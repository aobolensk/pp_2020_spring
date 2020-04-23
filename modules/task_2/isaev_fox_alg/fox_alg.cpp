// Copyright 2020 Isaev Ilya
#include "../../../modules/task_2/isaev_fox_alg/fox_alg.h"
#include <omp.h>
#include <cmath>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <iostream>

Matrix getRandomMatrix(const int& n) {
    if (n <= 0) {
        throw std::exception();
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 100);

    Matrix res(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = dis(gen);
        }
    }
    return res;
}

Matrix naiveMultiplication(const Matrix& mat1, const Matrix& mat2) {
    if (mat1[0].size() != mat2.size())
        throw std::exception();

    size_t n = mat1.size();
    size_t m = mat2[0].size();
    Matrix res(n, std::vector<double>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            res[i][j] = 0;
            for (size_t k = 0; k < mat2.size(); ++k) {
                res[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
    return res;
}

Matrix blockMultiplication(const Matrix& mat1, const Matrix& mat2) {
    if (!isSquared(mat1) || !isSquared(mat2) || mat1.size() != mat2.size())
        throw std::logic_error("Matrix should be squared");
    size_t n = mat1.size();
    size_t q = n / std::sqrt(n);
    size_t block_size = n / q;
    Matrix res(n, std::vector<double>(n));

    for (size_t jj = 0; jj < n; jj+=block_size) {
        for (size_t kk = 0; kk < n; kk+=block_size) {
            for (size_t i = 0; i < n; ++i) {
                for (size_t j = jj; j < std::min(jj+block_size, n); ++j) {
                    for (size_t k = kk; k < std::min(kk+block_size, n); ++k) {
                        res[i][j] += mat1[i][k] * mat2[k][j];
                    }
                }
            }
        }
    }

    return res;
}

bool matrixComparison(const Matrix& mat1, const Matrix& mat2) {
    if (mat1.size() != mat2.size() || mat1[0].size() != mat2[0].size())
        throw std::logic_error("Matrixes have different size");
    bool isequal = true;
    for (size_t i = 0; i < mat1.size() && isequal; ++i) {
        for (size_t j = 0; j < mat1[0].size(); ++j)
            if (!doubleComparison(mat1[i][j], mat2[i][j])) {
                std::cout << mat1[i][j] << " " << mat2[i][j] << std::endl;
                isequal = false;
                break;
            }
    }
    return isequal;
}

Matrix foxAlgParallel(const Matrix& mat1, const Matrix& mat2, const unsigned& n_threads) {
    if (!isSquared(mat1) || !isSquared(mat2) || mat1.size() != mat2.size())
        throw std::logic_error("Matrix should be squared");

    size_t n = mat1.size();
    size_t q = std::sqrt(n_threads);
    size_t block_size = n / q;


    auto mat1_clone = mat1;
    auto mat2_clone = mat2;

    auto old_n = n;
    while (n%q != 0) {
        mat1_clone.push_back(std::vector<double>(n, 0));
        mat2_clone.push_back(std::vector<double>(n, 0));
        std::for_each(mat1_clone.begin(), mat1_clone.end(), [](std::vector<double>& a){a.push_back(0);});
        std::for_each(mat2_clone.begin(), mat2_clone.end(), [](std::vector<double>& a){a.push_back(0);});
        n++;
        block_size = n / q;
    }

    Matrix res(n, std::vector<double>(n));
    #pragma omp parallel num_threads(q*q)
    {
        auto thread_i = omp_get_thread_num() / q;
        auto thread_j = omp_get_thread_num() % q;

        Matrix A(block_size), B(block_size), C(block_size, std::vector<double>(block_size, 0));

        for (size_t step = 0; step < q; ++step) {
            auto k_bar = (thread_i+step) % q;
            for (size_t k = 0; k < block_size; ++k) {
                A[k] = std::vector<double>(mat1_clone[thread_i * block_size+k].begin()+(k_bar*block_size),
                                          mat1_clone[thread_i * block_size+k].begin()+(k_bar*block_size+block_size));
                B[k] = std::vector<double>(mat2_clone[k_bar * block_size+k].begin()+(thread_j*block_size),
                                           mat2_clone[k_bar * block_size+k].begin()+(thread_j*block_size+block_size));
            }
            for (size_t i = 0; i < block_size; ++i) {
                for (size_t j = 0; j < block_size; ++j) {
                    for (size_t kk = 0; kk < block_size; ++kk)
                    C[i][j] += A[i][kk]*B[kk][j];
                }
            }
        }

        for (size_t i = 0; i < block_size; ++i) {
            for (size_t j = 0; j < block_size; ++j) {
                auto res_i = i+thread_i*block_size;
                auto res_j = j+thread_j*block_size;
                res[res_i][res_j] = C[i][j];
            }
        }
    }
    if (n != old_n) {
        #pragma omp parallel for
        for (int i = 0; i < static_cast<int>(old_n); ++i) {
            res[i].resize(old_n);
        }
    }
    res.resize(old_n);
    return res;
}
