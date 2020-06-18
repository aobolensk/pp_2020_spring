// Copyright 2020 Shemetov Philipp

#include <cmath>
#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>
#include "../../../modules/task_4/shemetov_p_sparse_matrix_CCS_complex/multi_matrix.h"
#include "../../../3rdparty/unapproved/unapproved.h"

typedef std::vector <std::vector<std::complex < double>>> mtxComplex;

SparseMatrixCCS::SparseMatrixCCS(size_t _m, size_t _n) {
    n = _n;
    m = _m;
}

SparseMatrixCCS::SparseMatrixCCS(size_t _m, size_t _n, size_t nonezero) {
    if (_m <= 0 || _n <= 0) {
        throw "Error: Input not less then zero";
    }
    n = _n;
    m = _m;
    value.resize(nonezero);
    row_index.resize(nonezero);
}

SparseMatrixCCS::SparseMatrixCCS(size_t _m, size_t _n, double sparseness) {
    if (_m <= 0 || _n <= 0) {
        throw "Error: Input size matrix not less then zero";
    }
    if (std::fabs(sparseness) < 0.5) {
        throw "Error: Input size matrix not less then zero";
    }
    m = _m;
    n = _n;
    mtxComplex vec(m);
    for (size_t i = 0; i < m; i++)
        vec[i].resize(n);
    std::mt19937 genReal{std::random_device()()};
    std::mt19937 genImag{std::random_device()()};
    std::mt19937 gen{std::random_device()()};
    std::uniform_int_distribution<int> randReal(0, 10), randImag(0, 10);
    std::uniform_real_distribution<> probability{0, 1};
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            if (probability(gen) >= sparseness) {
                vec[i][j].real(randReal(genReal));
                vec[i][j].imag(randImag(genImag));
            }
        }
    }
    size_t i, j;
    int col_offsets_count = 0;
    m = vec.size();
    n = vec[0].size();
    col_offsets.push_back(0);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (vec[i][j].imag() != 0 || vec[i][j].real() != 0) {
                col_offsets_count++;
                value.push_back(vec[i][j]);
                row_index.push_back(j);
            }
        }
        col_offsets.push_back(col_offsets_count);
    }
}

SparseMatrixCCS::SparseMatrixCCS(size_t _m, size_t _n,
                                 std::vector <std::complex<double>> _value,
                                 std::vector<int> _row_index,
                                 std::vector<int> _col_offsets) {
    m = _m;
    n = _n;
    value = _value;
    row_index = _row_index;
    col_offsets = _col_offsets;
}

SparseMatrixCCS::SparseMatrixCCS(const SparseMatrixCCS &obj) {
    n = obj.n;
    m = obj.m;
    value = obj.value;
    row_index = obj.row_index;
    col_offsets = obj.col_offsets;
}

SparseMatrixCCS SparseMatrixCCS::transpose() {
    int tempColIndex, index;
    SparseMatrixCCS at(m, n, value.size());
    std::vector<int> tempCountCol(n, 0);
    at.col_offsets.push_back(0);
    for (size_t i = 0; i < m; i++)
        for (int j = col_offsets[i]; j < col_offsets[i + 1]; j++) {
            tempColIndex = row_index[j];
            tempCountCol[tempColIndex]++;
        }
    for (size_t j = 0; j < n; j++) {
        at.col_offsets.push_back(at.col_offsets[j] + tempCountCol[j]);
    }

    for (size_t j = 0; j < n; j++)
        tempCountCol[j] = 0;

    for (size_t i = 0; i < m; i++) {
        for (int j = col_offsets[i]; j < col_offsets[i + 1]; j++) {
            tempColIndex = row_index[j];
            index = at.col_offsets[tempColIndex] + tempCountCol[tempColIndex];
            at.row_index[index] = i;
            at.value[index] = value[j];
            tempCountCol[tempColIndex]++;
        }
    }
    return at;
}

SparseMatrixCCS::SparseMatrixCCS(const mtxComplex &mt) {
    mtxComplex vec = mt;
    int col_offsets_count = 0;
    m = vec.size();
    n = vec[0].size();
    col_offsets.push_back(0);
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            if (vec[i][j].imag() != 0 || vec[i][j].real() != 0) {
                col_offsets_count++;
                value.push_back(vec[i][j]);
                row_index.push_back(j);
            }
        }
        col_offsets.push_back(col_offsets_count);
    }
}

SparseMatrixCCS SparseMatrixCCS::MultiplySparseMatrix(
        const SparseMatrixCCS &A, const SparseMatrixCCS &B) {
    if (A.n != B.m) {
        throw "Error(Size col matrix A not equal size row matrix B)";
    }
    SparseMatrixCCS resMatrix(A.m, B.n);
    int tempRowA;
    resMatrix.col_offsets.push_back(0);
    std::vector <std::complex<double>> tempDataVec(A.m + 1, {0, 0});

    for (size_t j = 0; j < B.n; j++) {
        for (int k = B.col_offsets[j]; k < B.col_offsets[j + 1]; k++) {
            tempRowA = B.row_index[k];
            for (int i = A.col_offsets[tempRowA];
                 i < A.col_offsets[tempRowA + 1]; i++) {
                tempDataVec[A.row_index[i]] += B.value[k] * A.value[i];
            }
        }
        for (size_t count = 0; count < A.m; count++) {
            if (tempDataVec[count].imag() != 0 ||
                tempDataVec[count].real() != 0) {
                resMatrix.row_index.push_back(count);
                resMatrix.value.push_back(tempDataVec[count]);
                tempDataVec[count] = 0;
            }
        }
        resMatrix.col_offsets.push_back(resMatrix.value.size());
    }
    return resMatrix;
}

SparseMatrixCCS SparseMatrixCCS::MultiplySparseMatrixSTD(
        const SparseMatrixCCS &A, const SparseMatrixCCS &B) {
    if (A.n != B.m) {
        throw "Error(Size col matrix A not equal size row matrix B)";
    }

    SparseMatrixCCS resMatrix(A.m, B.n);
    resMatrix.col_offsets.push_back(0);
    std::vector < std::vector < std::complex < double >> > tempVecValue(B.n);
    std::vector <std::vector<int>> tempVecRowIndex(B.n);
    std::vector<int> tempVecColPtr(B.n, 0);
    const int nthreads = (B.n >= 4) ? std::thread::hardware_concurrency() : B.n;
    const int delta = B.n / nthreads;
    const int deltaReminder = B.n % nthreads;
    std::thread *threads = new std::thread[nthreads];

    for (int s = 0; s < nthreads; s++) {
        int deltaTemp = (s < 3) ? (s+1)*delta : (s+1)*delta + deltaReminder;
        threads[s] = std::thread([&tempVecValue, &tempVecRowIndex,
        &tempVecColPtr, A, B,deltaTemp, s, delta]() {
            for (int j = s*delta; j < deltaTemp; j++) {
                int tempRowA = 0;
                std::vector <std::complex<double>> tempDataVec(A.m + 1, {0, 0});
                    for (int k = B.col_offsets[j]; k < B.col_offsets[j + 1]; k++) {
                        tempRowA = B.row_index[k];
                        for (int i = A.col_offsets[tempRowA];
                            i < A.col_offsets[tempRowA + 1]; i++) {
                            tempDataVec[A.row_index[i]] += B.value[k] * A.value[i];
                        }
                    }
                    for (size_t count = 0; count < A.m; count++) {
                        if (tempDataVec[count].imag() != 0 ||
                            tempDataVec[count].real() != 0) {
                            tempVecRowIndex[j].push_back(count);
                            tempVecValue[j].push_back(tempDataVec[count]);
                            tempVecColPtr[j]++;
                        }
                    }
                }
            });
    }
    for (int s = 0; s < nthreads; s++) {
        threads[s].join();
    }

    int varTemp = 0;
    for (size_t i = 0; i < resMatrix.n; i++) {
        varTemp += tempVecColPtr[i];
        resMatrix.col_offsets.push_back(varTemp);
    }

    for (size_t i = 0; i < tempVecRowIndex.size(); i++)
    {
        resMatrix.row_index.insert(resMatrix.row_index.end(),tempVecRowIndex[i].begin(),tempVecRowIndex[i].end());
        resMatrix.value.insert(resMatrix.value.end(),tempVecValue[i].begin(),tempVecValue[i].end());
    }

    delete[] threads;
    return resMatrix;
}

mtxComplex multiMatrix(const mtxComplex &mtxA, const mtxComplex &mtxB) {
    if (mtxA[0].size() != mtxB.size()) {
        throw "Error(Size col matrix A not equal size row matrix B)";
    }
    mtxComplex matrix(mtxA.size());
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix[i].resize(mtxB[0].size());
    }

    for (size_t i = 0; i < mtxA.size(); i++) {
        for (size_t j = 0; j < mtxB[0].size(); j++) {
            matrix[i][j] = 0;
            for (size_t k = 0; k < mtxA[0].size(); k++) {
                matrix[i][j] += mtxA[i][k] * mtxB[k][j];
            }
        }
    }
    return matrix;
}

bool SparseMatrixCCS::operator==(const SparseMatrixCCS &newMtx) const {
    if ((value != newMtx.value) || (row_index != newMtx.row_index) ||
        (col_offsets != newMtx.col_offsets) || (m != newMtx.m) ||
        (n != newMtx.n)) {
        return false;
    } else {
        return true;
    }
}


//  Debug
// void Print(const mtxComplex &mt) {
//     for (size_t i = 0; i < mt.size(); i++) {
//         for (size_t j = 0; j < mt[0].size(); j++)
//             std::cout << mt[i][j] << " \n"[j == mt[0].size() - 1];
//     }
// }

//  Debug
// void SparseMatrixCCS::PrintCCS() {
//     std::cout << "Value:" << std::endl;
//     for (size_t i = 0; i < value.size(); i++) {
//         std::cout << value[i] << "|";
//     }
//     std::cout << "rowIndex:" << std::endl;
//     for (size_t i = 0; i < row_index.size(); i++) {
//         std::cout << row_index[i] << "|";
//     }
//     std::cout << "col_offsets:" << std::endl;
//     for (size_t i = 0; i < col_offsets.size(); i++) {
//         std::cout << col_offsets[i] << "|";
//     }
// }





