// Copyright 2020 Shemetov Philipp


#include <cmath>
#include <random>
#include <iostream>
#include <vector>
#include "../../../modules/task_1/shemetov_p_sparse_matrix_CCS_complex/multi_matrix.h"

SparseMatrixCCS::SparseMatrixCCS(size_t _m, size_t _n) {
    n = _n;
    m = _m;
}

SparseMatrixCCS::SparseMatrixCCS(size_t _m, size_t _n, size_t nonezero) {
    if (_m <= 0 || _n <= 0 || nonezero <= 0) {
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
    size_t x = (n > m ? n : m);
    SparseMatrixCCS at(n, m, value.size());
    std::vector<int> tempCountRow(x, 0);
    at.col_offsets.push_back(0);
    for (size_t i = 0; i < m; i++)
        for (int j = col_offsets[i]; j < col_offsets[i + 1]; j++) {
            tempColIndex = row_index[j];
            tempCountRow[tempColIndex]++;
        }

    for (size_t j = 0; j < n; j++) {
        at.col_offsets.push_back(at.col_offsets[j] + tempCountRow[j]);
    }

    for (size_t j = 0; j < x; j++)
        tempCountRow[j] = 0;

    for (size_t i = 0; i < m; i++) {
        for (int j = col_offsets[i]; j < col_offsets[i + 1]; j++) {
            tempColIndex = row_index[j];
            index = at.col_offsets[tempColIndex];
            at.row_index[index] = i;
            at.value[index] = value[j];
            tempCountRow[tempColIndex]++;
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
    SparseMatrixCCS tempMatrix(A.m, B.n);
    tempMatrix.col_offsets.push_back(0);
    std::vector <std::complex<double>> tempDataVec(A.n, {0, 0});
    for (size_t i = 0; i < A.m; i++) {
        for (int j = A.col_offsets[i]; j < A.col_offsets[i + 1]; j++) {
            int tempColumnA = A.row_index[j];
            for (int t = B.col_offsets[tempColumnA];
                 t < B.col_offsets[tempColumnA + 1]; t++) {
                tempDataVec[B.row_index[t]] += A.value[j] * B.value[t];
            }
        }
        for (size_t count = 0; count < A.n; count++) {
            if (tempDataVec[count].imag() != 0 ||
                tempDataVec[count].real() != 0) {
                tempMatrix.row_index.push_back(count);
                tempMatrix.value.push_back(tempDataVec[count]);
                tempDataVec[count] = 0;
            }
        }
        tempMatrix.col_offsets.push_back(tempMatrix.value.size());
    }
    return tempMatrix;
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
    if ((value != newMtx.value) && (row_index != newMtx.row_index) &&
        (col_offsets != newMtx.col_offsets) && (m != newMtx.m) &&
        (n != newMtx.n)) {
        return false;
    } else {
        return true;
    }
}


//  Debug
void Print(const mtxComplex &mt) {
    for (size_t i = 0; i < mt.size(); i++) {
        for (size_t j = 0; j < mt[0].size(); j++)
            std::cout << mt[i][j] << " \n"[j == mt[0].size() - 1];
    }
}

//  Debug
void SparseMatrixCCS::PrintCCS() {
    std::cout << "Value:" << std::endl;
    for (size_t i = 0; i < value.size(); i++) {
        std::cout << value[i] << "|";
    }
    std::cout << "rowIndex:" << std::endl;
    for (size_t i = 0; i < row_index.size(); i++) {
        std::cout << row_index[i] << "|";
    }
    std::cout << "col_offsets:" << std::endl;
    for (size_t i = 0; i < col_offsets.size(); i++) {
        std::cout << col_offsets[i] << "|";
    }
}






