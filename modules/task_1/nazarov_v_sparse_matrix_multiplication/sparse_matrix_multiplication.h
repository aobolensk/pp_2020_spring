// Copyright 2020 Nazarov Vladislav
#ifndef MODULES_TASK_1_NAZAROV_V_SPARSE_MATRIX_MULTIPLICATION_SPARSE_MATRIX_MULTIPLICATION_H_
#define MODULES_TASK_1_NAZAROV_V_SPARSE_MATRIX_MULTIPLICATION_SPARSE_MATRIX_MULTIPLICATION_H_

#include <vector>
#include <complex>
#include <iostream>
#include <cmath>

using cpx = std::complex<double>;

class CRS_Matrix {
    std::vector<cpx> val;
    std::vector<size_t> colIndex;
    std::vector<size_t> rowIndex;
    size_t row, col;
 public:
    explicit CRS_Matrix(const std::vector<std::vector<cpx>>& matrix);
    CRS_Matrix(const std::vector<cpx>& _val, const std::vector<size_t>& _colIndex,
        const std::vector<size_t>& _rowIndex, const size_t& _col, const size_t& _row) :
        val(_val), colIndex(_colIndex), rowIndex(_rowIndex), row(_row), col(_col) {}
    explicit CRS_Matrix(const size_t& valSize = 0, const size_t& colSize = 0, const size_t& rowSize = 0,
        const size_t& _col = 0, const size_t& _row = 0) : val(valSize, 0), colIndex(colSize, 0),
        rowIndex(rowSize, 0), row(_row), col(_col) {}
    bool operator== (const CRS_Matrix& mat) const&;
    CRS_Matrix operator* (const CRS_Matrix& mat) const&;
    CRS_Matrix transpose();
    std::vector<cpx> getVal() {return val;}
    std::vector<size_t> getColIndex() {return colIndex;}
    std::vector<size_t> getRowIndex() {return rowIndex;}
    void print();
};

std::vector<std::vector<cpx>> naiveMultiplication(const std::vector<std::vector<cpx>>& matrix1,
    const std::vector<std::vector<cpx>>& matrix2);
std::vector<std::vector<cpx>> getRandomSparseMatrix(const size_t& col, const size_t& row, const double& percent);

#endif  // MODULES_TASK_1_NAZAROV_V_SPARSE_MATRIX_MULTIPLICATION_SPARSE_MATRIX_MULTIPLICATION_H_
