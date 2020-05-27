// Copyright 2020 Antipin Alexander
#ifndef MODULES_TASK_3_ANTIPIN_A_MATRIX_MULTIPLICATION_TBB_MATRIX_MULTIPLICATION_H_
#define MODULES_TASK_3_ANTIPIN_A_MATRIX_MULTIPLICATION_TBB_MATRIX_MULTIPLICATION_H_

#include <tbb/tbb.h>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

enum type {
    CRS,
    CCS
};

template <type T = CCS>
class SparseMatrix {
 public:
    explicit SparseMatrix(const size_t size = 1, const uint16_t coeff = 6);
    SparseMatrix(const SparseMatrix<T>& mat);
    void getRandomMatrix(const size_t size, const uint16_t coeff);
    double getElem(const size_t i, const size_t j) const;
    void setElem(const double elem, const size_t i, const size_t j);
    void setMatrix(const std::vector<double>& A, const std::vector<size_t>& LI, const std::vector<size_t>& LJ,
        const size_t n);
    size_t getMatrixSize() const;
    size_t getRealSize() const;
    void printM() const;

    friend void convertMatrix(const SparseMatrix<CCS>& A, SparseMatrix<CRS>* B);
    friend void convertMatrix(const SparseMatrix<CRS>& A, SparseMatrix<CCS>* B);
    friend void getParallelTBBMatrixMultiplication(const SparseMatrix<CCS>& A, const SparseMatrix<CCS>& B,
        SparseMatrix<CCS>* C, const int numThreads);
 private:
    std::vector<double> A;
    std::vector<size_t> LI;
    std::vector<size_t> LJ;
    size_t n;
};

template <type T>
SparseMatrix<T>::SparseMatrix(const size_t size, const uint16_t coeff) {
    if (coeff <= 5) {
        throw("So small coefficient, it is not a sparse matrix");
    }
    n = size;
    size_t realSize = (size * size) / coeff;
    A.resize(realSize);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 2);
    for (double& val : A) {
        val = 100 - dist(gen) * 50;
    }
    if (T == CCS) {
        LI.resize(realSize);
        LJ.resize(size + 1);
        for (size_t& val : LI) {
            val = gen() % (size * size);
        }
        std::sort(LI.begin(), LI.end());
        size_t colCounter = 0;
        uint32_t j = 0;
        for (uint32_t i = 0; i < realSize; ) {
            if (i != 0 && (LI[i] % size) == LI[i - 1]) {
                LI.erase(LI.begin() + i);
                A.erase(A.begin() + i);
                --realSize;
                continue;
            }
            if (LI[i] / size >= colCounter) {
                LJ[j] = i;
                ++j;
                ++colCounter;
            }
            LI[i] = LI[i] % size;
            ++i;
        }
        while (j != LJ.size()) {
            LJ[j] = realSize;
            ++j;
        }
    } else if (T == CRS) {
        LJ.resize(realSize);
        LI.resize(size + 1);
        for (size_t& val : LJ) {
            val = gen() % (size * size);
        }
        std::sort(LJ.begin(), LJ.end());
        size_t rowCounter = 0;
        uint32_t i = 0;
        for (uint32_t j = 0; j < realSize; ) {
            if (j != 0 && (LJ[j] % size) == LJ[j - 1]) {
                LJ.erase(LJ.begin() + i);
                A.erase(A.begin() + i);
                --realSize;
                continue;
            }
            if (LJ[j] / size >= rowCounter) {
                LI[i] = j;
                ++i;
                ++rowCounter;
            }
            LJ[j] = LJ[j] % size;
            ++j;
        }
        while (i != LI.size()) {
            LI[i] = realSize;
            ++i;
        }
    }
}

template <type T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& mat) {
    n = mat.n;
    A = mat.A;
    LI = mat.LI;
    LJ = mat.LJ;
}

template <type T>
void SparseMatrix<T>::getRandomMatrix(const size_t size, const uint16_t coeff) {
    n = size;
    size_t realSize = (size * size) / coeff;
    A.resize(realSize);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 2);
    for (double& val : A) {
        val = 100 - dist(gen) * 50;
    }
    if (T == CCS) {
        LI.resize(realSize);
        LJ.resize(size + 1);
        for (size_t& val : LI) {
            val = gen() % (size * size);
        }
        std::sort(LI.begin(), LI.end());
        int colCounter = 0;
        uint32_t j = 0;
        for (uint32_t i = 0; i < realSize; ) {
            if (i != 0 && (LI[i] % size) == LI[i - 1]) {
                LI.erase(LI.begin() + i);
                A.erase(A.begin() + i);
                --realSize;
                continue;
            }
            if (LI[i] / size > colCounter) {
                LJ[j] = i;
                ++j;
                ++colCounter;
            }
            LI[i] = LI[i] % size;
            ++i;
        }
    } else if (T == CRS) {
        LJ.resize(realSize);
        LI.resize(size + 1);
        for (size_t& val : LJ) {
            val = gen() % (size * size);
        }
        std::sort(LJ.begin(), LJ.end());
        int rowCounter = 0;
        uint32_t i = 0;
        for (uint32_t j = 0; j < realSize; ) {
            if (j != 0 && (LJ[j] % size) == LJ[j - 1]) {
                LJ.erase(LJ.begin() + i);
                A.erase(A.begin() + i);
                --realSize;
                continue;
            }
            if (LJ[j] / size > rowCounter) {
                LI[i] = j;
                ++i;
                ++rowCounter;
            }
            LJ[j] = LJ[j] % size;
            ++j;
        }
    }
}

template <type T>
double SparseMatrix<T>::getElem(const size_t i, const size_t j) const {
    size_t count = T == CCS ? LJ.size() - 1 : LI.size() - 1;
    if (i > count || j > count) {
        throw("Wrong index of element");
    }
    double res = 0.0;
    if (T == CCS) {
        for (size_t k = LJ[j]; k < LJ[j + 1]; ++k) {
            if (LI[k] == i) {
                res = A[k];
                break;
            }
        }
    } else if (T == CRS) {
        for (size_t k = LI[i]; k < LI[i + 1]; ++k) {
            if (LJ[k] == j) {
                res = A[k];
                break;
            }
        }
    }
    return res;
}

template <type T>
void SparseMatrix<T>::setElem(const double elem, const size_t i, const size_t j) {
    if (A.size() < i || A.size() < j || i < 0 || j < 0) {
        throw("Out of matrix range");
    }
}

template <type T>
void SparseMatrix<T>::setMatrix(const std::vector<double>& A, const std::vector<size_t>& LI,
    const std::vector<size_t>& LJ, const size_t n) {
    size_t count = T == CCS ? LI.size() : LJ.size();
    if (A.size() != count) {
        throw("Wrong vectors size");
    }
    this->n = n;
    this->A = A;
    this->LI = LI;
    this->LJ = LJ;
}

template <type T>
size_t SparseMatrix<T>::getMatrixSize() const {
    return n;
}

template <type T>
size_t SparseMatrix<T>::getRealSize() const {
    return A.size();
}

template <type T>
void SparseMatrix<T>::printM() const {
    if (T == CCS) {
        for (size_t i = 0; i < A.size(); ++i) {
            printf("A[%ld] = %f, LI[%ld] = %ld\n", i, A[i], i, LI[i]);
        }
        for (size_t i = 0; i < LJ.size(); ++i) {
            printf("LJ[%ld] = %ld\n", i, LJ[i]);
        }
    } else {
        for (size_t i = 0; i < A.size(); ++i) {
            printf("A[%ld] = %f, LJ[%ld] = %ld\n", i, A[i], i, LJ[i]);
        }
        for (size_t i = 0; i < LI.size(); ++i) {
            printf("LI[%ld] = %ld\n", i, LI[i]);
        }
    }
}

void constructMatrix(const SparseMatrix<CCS>& A, std::vector<double>* B);

void matrixMultiplication(const std::vector<double>& A, const size_t n, const std::vector<double>& B,
    std::vector<double>* C);

double isZero(const double nomber);

void getRandomMatrix(std::vector<double>* A, const size_t n);

void convertMatrix(const SparseMatrix<CCS>& A, SparseMatrix<CRS>* B);

void convertMatrix(const SparseMatrix<CRS>& A, SparseMatrix<CCS>* B);

void getParallelTBBMatrixMultiplication(const SparseMatrix<CCS>& A, const SparseMatrix<CCS>& B, SparseMatrix<CCS>* C,
    const int numThreads = 2);

#endif  // MODULES_TASK_3_ANTIPIN_A_MATRIX_MULTIPLICATION_TBB_MATRIX_MULTIPLICATION_H_
