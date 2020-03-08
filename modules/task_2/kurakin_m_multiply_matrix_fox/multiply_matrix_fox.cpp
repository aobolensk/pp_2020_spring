// Copyright 2020 Kurakin Mikhail
#include "../../../modules/task_2/kurakin_m_multiply_matrix_fox/multiply_matrix_fox.h"
#include <math.h>
#include <omp.h>
#include <random>
#include <vector>
#include <iostream>
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

bool canUseFoxAlg(const matrix &a, const matrix &b) {
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

bool algFoxMatrixMultiply(const matrix &a, const matrix &b, matrix *out) {
    // uint numThreads = omp_get_num_threads();
    if (!canUseFoxAlg(a, b)) return false;
    uint size = a.size();
    // uint grid = std::sqrt(numThreads);
    // uint blockSize = size / grid;
    std::vector<double> aBlock(size, 0.0);
    matrix bBlock;
    matrix cBlock;
    prepareOutMatrix(&cBlock, size, size);
    prepareOutMatrix(&bBlock, size, size);
    prepareOutMatrix(out, size, size);
    // std::cout << blockSize << "b\n" << size<<"s\n" << "grid = "<< grid <<
    // "Threds = " << numThreads<<std::endl;
    omp_lock_t mylock;
    omp_init_lock(&mylock);
#pragma omp parallel firstprivate(aBlock, bBlock, cBlock)
    {
        uint numThreads = omp_get_num_threads();
        uint grid = std::sqrt(numThreads);
        uint blockSize = size / grid;
        uint thread_coord1 = omp_get_thread_num() / grid;
        uint thread_coord2 = omp_get_thread_num() % grid;
        uint k1 = thread_coord1 * blockSize;  // wrong
        uint k2 = thread_coord2 * blockSize;  // wrong
        // omp_set_lock(&mylock);
        // if (omp_get_thread_num() == 0) {
        //     for (uint i = 0; i < a.size(); i++) {
        //         for (uint j = 0; j < a.size(); j++) {
        //             std::cout << b[i][j] << std::endl;
        //         }
        //     }
        // }
        // // std::cout << blockSize << "b\n";
        // // std::cout << "(" << k1 << ", " << k2 << ")  "
        // //           << "numbeThr = " << omp_get_thread_num() << std::endl;
        // omp_unset_lock(&mylock);
        for (uint i = 0; i < blockSize; i++) {  // формирование обработка блока
            for (uint j = 0; j < blockSize; j++) {  //заполнение блоков матрицы
                uint s = (i + j) % blockSize;
                aBlock[j] = a[j + k1][s + k2];
                for (uint k = 0; k < blockSize; k++) {
                    bBlock[j][k] = b[s + k1][k + k2];
                }
            }
            for (uint j = 0; j < blockSize; j++) {  // Compute C
                for (uint k = 0; k < blockSize; k++) {
                    cBlock[j][k] += aBlock[j] * bBlock[j][k];
                }
            }
            // omp_set_lock(&mylock);
            // if (omp_get_thread_num() == 0) {
            //     for (uint i = 0; i < blockSize; i++) {
            //         std::cout << "thread = " << omp_get_thread_num()
            //                   <<"\n" << aBlock[i] << std::endl;
            //         for (uint j = 0; j < blockSize; j++) {
            //             // std::cout << "bBlock =" << bBlock[i][j] << std::endl;
            //             std::cout << "cBlock =" << cBlock[i][j] << std::endl;
            //         }
            //     }
            // }
            // if (omp_get_thread_num() == 1) {
            //     for (uint i = 0; i < blockSize; i++) {
            //         std::cout << "thread = " << omp_get_thread_num()
            //                   <<"\n" << aBlock[i] << std::endl;
            //         for (uint j = 0; j < blockSize; j++) {
            //             // std::cout << "bBlock =" << bBlock[i][j] << std::endl;
            //             std::cout << "cBlock =" << cBlock[i][j] << std::endl;
            //         }
            //     }
            // }
            // if (omp_get_thread_num() == 2) {
            //     for (uint i = 0; i < blockSize; i++) {
            //         std::cout << "thread = " << omp_get_thread_num()
            //                   <<"\n" << aBlock[i] << std::endl;
            //         for (uint j = 0; j < blockSize; j++) {
            //             // std::cout << "bBlock =" << bBlock[i][j] << std::endl;
            //             std::cout << "cBlock =" << cBlock[i][j] << std::endl;
            //         }
            //     }
            // }
            // if (omp_get_thread_num() == 3) {
            //     for (uint i = 0; i < blockSize; i++) {
            //         std::cout << "thread = " << omp_get_thread_num()
            //                   <<"\n" << aBlock[i] << std::endl;
            //         for (uint j = 0; j < blockSize; j++) {
            //             // std::cout << "bBlock =" << bBlock[i][j] << std::endl;
            //             std::cout << "cBlock =" << cBlock[i][j] << std::endl;
            //         }
            //     }
            // }
            // omp_unset_lock(&mylock);
        }
        //объединть все блоки в единый массив
        for (uint i = 0; i < blockSize; i++) {
            for (uint j = 0; j < blockSize; j++) {
                (*out)[i + k1][j + k2] = cBlock[i][j];
            }
        }
    }
    return true;
}

// void getThredPos(uint grid, uint *k1, uint *k2) {
//     (*k1)=omp_get_thread_num() / grid;
//     (*k2) = omp_get_thread_num() %grid;
// }
