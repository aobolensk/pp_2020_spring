// Copyright 2020 Antipin Alexander
#include <thread>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include "../../../modules/task_4/antipin_a_matrix_multiplication_std/matrix_multiplication.h"

void constructMatrix(const SparseMatrix<CCS>& A, std::vector<double>* B) {
    size_t n = A.getMatrixSize();
    (*B).resize(n*n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            (*B)[i * n + j] = A.getElem(i, j);
        }
    }
}

void matrixMultiplication(const std::vector<double>& A, const size_t n, const std::vector<double>& B,
    std::vector<double>* C) {
    if (A.size() != B.size()) {
        throw("Wrong matrix size");
    }
    (*C).resize(A.size(), 0.0);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                (*C)[i * n + j] += isZero(A[i * n + k] * B[k * n + j]);
            }
        }
    }
}

double isZero(const double number) {
    if (std::abs(number) < 0.0000000001) {
        return 0.0;
    } else {
        return number;
    }
}

void getRandomMatrix(std::vector<double>* A, const size_t n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 2);

    A->resize(n);
    for (double& elem : (*A)) {
        elem = 100 - dist(gen) * 50;
    }
}

void convertMatrix(const SparseMatrix<CCS>& A, SparseMatrix<CRS>* B) {
    B->A.resize(A.getRealSize());
    B->LI.resize(A.getMatrixSize() + 1);
    B->LJ.resize(A.getRealSize());
    B->n = A.n;

    std::vector<size_t> cols(A.getRealSize());
    for (int lj = 0; lj < static_cast<int>(A.getMatrixSize()); ++lj) {
        for (size_t i = A.LJ[lj]; i < A.LJ[lj + 1]; ++i) {
            cols[i] = lj;
        }
    }
    size_t li = 0;
    for (size_t n = 0; n < A.getMatrixSize(); ++n) {
        for (size_t i = 0; i < A.getRealSize(); ++i) {
            if (A.LI[i] == n) {
                B->A[li] = A.A[i];
                B->LJ[li] = cols[i];
                ++li;
            }
        }
        B->LI[n + 1] = li;
    }
}

void convertMatrix(const SparseMatrix<CRS>& A, SparseMatrix<CCS>* B) {
    B->A.resize(A.getRealSize());
    B->LJ.resize(A.getMatrixSize() + 1);
    B->LI.resize(A.getRealSize());
    B->n = A.n;

    std::vector<size_t> rows(A.getRealSize());
    for (size_t li = 0; li < A.getMatrixSize(); ++li) {
        for (size_t j = A.LI[li]; j < A.LI[li + 1]; ++j) {
            rows[j] = li;
        }
    }

    size_t lj = 0;
    for (size_t n = 0; n < A.getMatrixSize(); ++n) {
        for (size_t j = 0; j < A.getRealSize(); ++j) {
            if (A.LJ[j] == n) {
                B->A[lj] = A.A[j];
                B->LI[lj] = rows[j];
                ++lj;
            }
        }
        B->LJ[n + 1] = lj;
    }
}

void parallelForMatrix(const SparseMatrix<CRS>& A, const SparseMatrix<CCS>& B, std::vector<std::vector<double>>* a,
    std::vector<std::vector<size_t>>* b, const size_t thread_number, const size_t count_of_thread) {
    size_t start = (A.getMatrixSize() / count_of_thread) * thread_number;
    size_t end = thread_number == count_of_thread - 1 ? A.getMatrixSize() :
        (A.getMatrixSize() / count_of_thread) * (thread_number + 1);
    size_t lj = start, iterator = 0;
    for (size_t n = start; n < end; ++n) {
        size_t li = 0;
        for (size_t i = 0; i < A.getMatrixSize(); ++i) {
            double elem = 0.0;
            bool isRow = (A.LI[i + 1] - A.LI[i]) < (B.LJ[lj + 1] - B.LJ[lj]) ? true : false;
            if (!isRow) {
                for (size_t j = B.LJ[lj]; j < B.LJ[lj + 1]; ++j) {
                    elem += isZero(A.getElem(i, B.LI[j]) * B.A[j]);
                }
            }
            else {
                for (size_t j = A.LI[i]; j < A.LI[i + 1]; ++j) {
                    elem += isZero(A.A[j] * B.getElem(A.LJ[j], n));
                }
            }
            if (elem != 0.0) {
                (*a)[n][iterator] = elem;
                (*b)[n][iterator] = li;
                ++(*b)[n][A.getMatrixSize()];
                ++iterator;
            }
            ++li;
        }
        ++lj;
        iterator = 0;
    }
}

void getParallelSTDMatrixMultiplication(const SparseMatrix<CCS>& A, const SparseMatrix<CCS>& B, SparseMatrix<CCS>* C,
    const int numThreads) {
    if (A.getMatrixSize() != B.getMatrixSize()) {
        throw("Matrices have a different range");
    }

    size_t iterator = 0;
    size_t numTr = static_cast<uint32_t>(numThreads) > std::thread::hardware_concurrency()
        ? std::thread::hardware_concurrency() : numThreads;
    numTr = numTr > A.getMatrixSize() ? A.getMatrixSize() : numTr;

    SparseMatrix<CRS> tmp;
    convertMatrix(A, &tmp);

    std::vector<std::vector<double>> a(A.getMatrixSize(), std::vector<double>(A.getMatrixSize()));
    std::vector<std::vector<size_t>> b(A.getMatrixSize(), std::vector<size_t>(A.getMatrixSize() + 1, 0));
    C->LJ.resize(A.getMatrixSize() + 1);

    std::thread* threads = reinterpret_cast<std::thread*>(operator new(sizeof(std::thread) * numTr));
    for (size_t i = 0; i < numTr; ++i)
        new(threads + i) std::thread(parallelForMatrix, std::ref(tmp), std::ref(B), &a, &b, i, numTr);

    for (size_t i = 0; i < numTr; ++i)
        threads[i].join();

    for (size_t i = 0; i < numTr; ++i)
        (threads + i)->~thread();
    operator delete(threads);

    iterator = 0;
    for (size_t i = 0; i < tmp.getMatrixSize(); ++i) {
        iterator += b[i][tmp.getMatrixSize()];
        C->LJ[i + 1] = iterator;
    }

    C->A.resize(iterator);
    C->LI.resize(iterator);

    iterator = 0;
    for (size_t i = 0; i < tmp.getMatrixSize(); ++i) {
        for (size_t j = 0; j < b[i][tmp.getMatrixSize()]; ++j) {
            C->A[iterator] = (a[i][j]);
            C->LI[iterator] = (b[i][j]);
            ++iterator;
        }
    }
}
