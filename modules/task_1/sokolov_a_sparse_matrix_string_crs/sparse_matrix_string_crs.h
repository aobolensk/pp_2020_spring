// Copyright 2020 Sokolov Andrey
#ifndef MODULES_TASK_1_SOKOLOV_A_SPARSE_MATRIX_STRING_CRS_SPARSE_MATRIX_STRING_CRS_H_
#define MODULES_TASK_1_SOKOLOV_A_SPARSE_MATRIX_STRING_CRS_SPARSE_MATRIX_STRING_CRS_H_
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <utility>
#include <algorithm>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

class SparseMatrix {
    size_t rows;
    size_t cols;
    std::vector<double> value;
    std::vector<size_t> colIndex;  // Column numbers for each item
    std::vector<size_t> rowIndex;  // Index of the beginning of each line
 public:
     SparseMatrix() : rows(0), cols(0) {}
     SparseMatrix(size_t _rows, size_t _cols,
                  std::vector<double> _value,
                  std::vector<size_t>    _colIndex,
                  std::vector<size_t>    _rowIndex);
     explicit SparseMatrix(const Matrix& matrix);
     SparseMatrix(const SparseMatrix& matrix) = default;
     SparseMatrix(size_t _rows, size_t _cols, size_t _elemsCount);

     bool operator== (const SparseMatrix& mat) const&;

     Matrix SparseToMatrix();

     void printDefault();
     void printMatrix();

     friend SparseMatrix SparseMatMul(const SparseMatrix& matrixA, const SparseMatrix& matrixB);
};

SparseMatrix SparseMatMul(const SparseMatrix& matrixA, const SparseMatrix& matrixB);
Matrix MatMul(const Matrix& matrixA, const Matrix& matrixB);

Matrix generateMatrix(const size_t& rows, const size_t& cols, const size_t& coeff);

void print(const Matrix& matrix);

#endif  // MODULES_TASK_1_SOKOLOV_A_SPARSE_MATRIX_STRING_CRS_SPARSE_MATRIX_STRING_CRS_H_
