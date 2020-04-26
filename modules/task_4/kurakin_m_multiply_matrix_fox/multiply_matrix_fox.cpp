// Copyright 2020 Kurakin Mikhail
#include "../../../modules/task_4/kurakin_m_multiply_matrix_fox/multiply_matrix_fox.h"

#include <math.h>
#include <random>
#include <thread>
#include <stdexcept>
#include <vector>
bool canMultiplicate(const matrix &a, const matrix &b) {
    if (a.empty() || b.empty()) return false;
    for (uint i = 0; i < a.size(); i++) {
        if (a[i].size() != b.size()) return false;
    }
    return true;
}

void prepareOutMatrix(matrix *matrixOut, uint sizeRow, uint sizeCol) {
    if ((*matrixOut).size() != sizeRow) (*matrixOut).resize(sizeRow);
    for (uint i = 0; i < (*matrixOut).size(); i++) {
        if ((*matrixOut)[i].size() != sizeCol) (*matrixOut)[i].resize(sizeCol);
        for (uint j = 0; j < (*matrixOut)[i].size(); j++) {
            (*matrixOut)[i][j] = 0;
        }
    }
}

bool simpleMaxtrixMultiply(const matrix &a, const matrix &b, matrix *out) {
    if (!canMultiplicate(a, b)) return false;
    prepareOutMatrix(out, a.size(), b.size());
    for (uint i = 0; i < a.size(); i++) {  // ixj j*k
        for (uint k = 0; k < b[0].size(); k++) {
            for (uint j = 0; j < b.size(); j++) {
                (*out)[i][k] += a[i][j] * b[j][k];
            }
        }
    }
    return true;
}

bool initMatrixRand(matrix *a, uint sizeRow, uint sizeCol) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1000.0, 1000.0);

    if ((*a).size() != sizeRow) (*a).resize(sizeRow);

    for (uint i = 0; i < sizeRow; i++) {
        if ((*a)[i].size() != sizeCol) (*a)[i].resize(sizeCol);

        for (uint j = 0; j < sizeCol; j++) {
            (*a)[i][j] = dis(gen);
        }
    }
    return true;
}

bool isSquareMatrix(const matrix &a, const matrix &b) {
    if (a.empty() || b.empty()) return false;
    if (a.size() != b.size()) return false;
    for (uint i = 0; i < a.size(); i++) {
        if (a[i].size() != a.size()) {
            return false;
        }
        if (a[i].size() != b[i].size()) return false;
    }
    return true;
}

void FoxAlgThreadFunc(const matrix &a, const matrix &b, matrix *out,
                      uint thread_number) {
    uint size = a.size();
    uint grid = sqrt(NTHREADS);  // NTHREADS perfect square
    uint blockSize = size / grid;

    uint thread_coord1 = thread_number / grid;
    uint thread_coord2 = thread_number % grid;

    uint k1 = thread_coord1 * blockSize;
    uint k2 = thread_coord2 * blockSize;

    std::vector<double> aBlock(blockSize, 0.0);
    matrix bBlock;
    matrix cBlock;
    prepareOutMatrix(&cBlock, blockSize, blockSize);
    prepareOutMatrix(&bBlock, blockSize, blockSize);

    if (size % grid == 0) {
        for (uint i = 0; i < size; i++) {  // формирование обработка блоков
            for (uint j = 0; j < blockSize; j++) {  //заполнение блоков матрицы
                uint s = (i + j + k1) % size;
                aBlock[j] = a[j + k1][s];
                for (uint k = 0; k < blockSize; k++) {
                    bBlock[j][k] = b[s][k + k2];
                }
            }
            for (uint j = 0; j < blockSize; j++) {  // Compute C
                for (uint k = 0; k < blockSize; k++) {
                    cBlock[j][k] += aBlock[j] * bBlock[j][k];
                }
            }
        }
        for (uint i = 0; i < blockSize; i++) {
            for (uint j = 0; j < blockSize; j++) {
                (*out)[i + k1][j + k2] = cBlock[i][j];
            }
        }
    }
}
bool algFoxMatrixMultiplyPar(const matrix &a, const matrix &b, matrix *out) {
    if (!isSquareMatrix(a, b)) return false;
    uint size = a.size();
    if ((size * size) % NTHREADS != 0)
        throw std::runtime_error(
            "size of matrix should devided by number of threads without "
            "reminder");
    prepareOutMatrix(out, size, size);
    std::thread threads[NTHREADS];
    for (uint l = 0; l < NTHREADS; l++) {
        threads[l] = std::thread(FoxAlgThreadFunc, a, b, out, l);
    }
    for (uint i = 0; i < NTHREADS; i++) {
        threads[i].join();
    }
    return true;
}

bool algFoxMatrixMultiplySeq(const matrix &a, const matrix &b, matrix *out) {
    uint numThread = 1;
    if (!isSquareMatrix(a, b)) return false;
    uint size = a.size();
    uint grid = std::sqrt(numThread);
    uint blockSize = size / grid;
    std::vector<double> aBlock(size, 0.0);
    matrix bBlock;
    prepareOutMatrix(out, size, size);
    prepareOutMatrix(&bBlock, size, size);

    for (uint i = 0; i < blockSize; i++) {  // формирование обработка блока
        for (uint j = 0; j < blockSize; j++) {  //заполнение блоков матрицы
            uint s = (i + j) % blockSize;
            aBlock[j] = a[j][s];
            for (uint k = 0; k < blockSize; k++) {
                bBlock[j][k] = b[s][k];
            }
        }
        for (uint j = 0; j < blockSize; j++) {  // Compute C
            for (uint k = 0; k < blockSize; k++) {
                (*out)[j][k] += aBlock[j] * bBlock[j][k];
            }
        }
    }
    return true;
}
