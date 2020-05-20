// Copyright 2020 Nechaeva Ekaterina

#include "../../../modules/task_4/nechaeva_e_matrix_Cannon_std/matrix_m_Cannon.h"
#include <thread>
#include <random>
#include <iostream>
#include <algorithm>
#include <exception>

matrix RandomMatrix(const int n) {
    if (n <= 0)
        throw std::invalid_argument("Negative size");

    std::mt19937 generator;
    std::random_device device;
    generator.seed(device());
    std::uniform_real_distribution<double> distribution(0, 100);;

    matrix rez(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rez[i][j] = distribution(generator);

    return rez;
}

matrix NaiveMulti(const matrix &A, const matrix &B) {
    if (A[0].size() != B.size())
        throw std::invalid_argument("Different values for col and row");

    size_t n = A[0].size();
    size_t m = A.size();
    size_t l = B[0].size();
    matrix rez(m, std::vector<double>(l, 0));

    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < l; j++)
            for (size_t k = 0; k < n; k++)
                rez[i][j] += A[i][k]*B[k][j];

    return rez;
}

bool CompareValues(const double &a, const double &b) {
    return std::fabs(a - b) < 0.00001;
}

bool CompareMatrix(const matrix &A, const matrix &B) {
    if (A[0].size() != B[0].size() || A.size() != B.size())
        return false;

    bool temp = true;
    for (size_t i = 0; i < A.size(); i++) {
        if (temp == false)
            break;
        for (size_t j = 0; j < A[0].size(); j++)
            if (!CompareValues(A[i][j], B[i][j])) {
                temp = false;
                break;
            }
    }

    return temp;
}

matrix BlockMulti(const matrix &A, const matrix &B, const int &blockSize) {
    if (A[0].size() != B.size())
        throw std::invalid_argument("Different values for col and row");
    int temp = blockSize;
    if (temp > static_cast<int>(A.size()))
        throw std::invalid_argument("Wrong blockSize");

    int n = A[0].size();
    int jjMin, kkMin;
    matrix rez(n, std::vector<double>(n, 0));

    for (int jj = 0; jj < n; jj += blockSize) {
        jjMin = std::min<int>(jj + blockSize, n);
       for (int kk = 0; kk < n; kk += blockSize) {
           kkMin = std::min<int>(kk+ blockSize, n);
           for (int i = 0; i < n; i++) {
               for (int k = kk; k < kkMin; k++) {
                   for (int j = jj; j < jjMin; j++) {
                      rez[i][j]  +=  A[i][k] * B[k][j];
                   }
                }
            }
        }
    }

    return rez;
}



matrix AlgorithmCannonSTD(const matrix &A, const matrix &B, const int &num_threads) {
    if (A[0].size() != B.size())
        throw std::invalid_argument("Different values for col and row");
    if (num_threads <= 0)
        throw std::invalid_argument("Wrong number of threads");

    std::thread* threads = new std::thread[num_threads];
    int n = A[0].size();
    int n_old = n;
    int q = std::sqrt(num_threads);
    matrix tempA = A;
    matrix tempB = B;

    if (n % q != 0) {
       while (n % q != 0) {
           tempA.push_back(std::vector<double>(n_old, 0));
           tempB.push_back(std::vector<double>(n_old, 0));
           n++;
       }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - n_old; ++j) {
                tempA[i].push_back(0);
                tempB[i].push_back(0);
            }
        }
    }
    int block_size = n / q;
    matrix rez(n, std::vector<double>(n));

    auto func = [&](int id_i_thread, int id_j_thread) {
        int thread_i = id_i_thread;
        int thread_j = id_j_thread;
        int block_i_A = 0, block_j_A = 0, block_i_B = 0, block_j_B = 0;

        matrix num1(block_size), num2(block_size),
            numrez(block_size, std::vector<double>(block_size, 0));

        for (int k = 0; k < block_size; ++k) {
            block_i_A = thread_i * block_size + k;
            block_j_A = ((thread_j + thread_i) % q) * block_size;
            block_j_B = thread_j * block_size;
            block_i_B = block_j_A + k;
            num1[k] = std::vector<double>(tempA[block_i_A].begin() + block_j_A,
                                        tempA[block_i_A].begin() + block_j_A + block_size);
            num2[k] = std::vector<double>(tempB[block_i_B].begin() + block_j_B,
                                        tempB[block_i_B].begin() + block_j_B + block_size);
        }
        for (int kk = 0; kk < q; ++kk) {
            for (int i = 0; i < block_size; ++i) {
                for (int j = 0; j < block_size; ++j) {
                    for (int s = 0; s < block_size; ++s) {
                        numrez[i][j] += num1[i][s] * num2[s][j];
                    }
                }
            }
            if (kk == q - 1) {
                break;
            }
            for (int k = 0; k < block_size; ++k) {
                int i_A = thread_i * block_size + k;
                int j_A = ((block_j_A / block_size + kk + 1) % q) * block_size;
                int i_B = ((block_i_B / block_size + kk + 1) % q) * block_size + k;
                int j_B = thread_j * block_size;
                num1[k] = std::vector<double>(tempA[i_A].begin() + j_A,
                                            tempA[i_A].begin() + j_A + block_size);
                num2[k] = std::vector<double>(tempB[i_B].begin() + j_B,
                                            tempB[i_B].begin() + j_B + block_size);
            }
        }
            for (int i = 0; i < block_size; ++i) {
                for (int j = 0; j < block_size; ++j) {
                    int ii = i + thread_i * block_size;
                    int jj = j + thread_j * block_size;
                    rez[ii][jj] = numrez[i][j];
                }
            }
    };
    int num = 0;
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < q; ++j) {
            threads[num] = std::thread(func, i, j);
            num++;
        }
    }
    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }
    auto func_resize = [&](int start, int temp_n) {
        for (auto i = start; i < temp_n; ++i ) {
                rez[i].resize(n_old);
        }
    };
    if (n_old != n) {
        std::thread* threads1 = new std::thread[block_size];
        for (int i = 0; i < block_size; ++i) {
            threads1[i] = std::thread(func_resize, i * q, i * q + q);
        }
        for (int j = 0; j < block_size; ++j) {
            threads1[j].join();
        }
        delete []threads1;
    }
    rez.resize(n_old);
    delete []threads;
    return rez;
}