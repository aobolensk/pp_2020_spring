// Copyright 2020 Sokolov Andrey
#ifndef MODULES_TASK_2_SOKOLOV_A_SPARSE_MATRIX_CRS_SPARSE_MATRIX_CRS_OMP_H_
#define MODULES_TASK_2_SOKOLOV_A_SPARSE_MATRIX_CRS_SPARSE_MATRIX_CRS_OMP_H_
#include <memory.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <utility>
#include <algorithm>
#include <vector>

using Matrix = std::vector<std::vector<double>>;

class SparseMatrix {
 public:
    int rows;
    int cols;
    std::vector<double> value;
    std::vector<int> colIndex;  // Column numbers for each item
    std::vector<int> rowIndex;  // Index of the beginning of each line
     SparseMatrix() : rows(0), cols(0) {}
     SparseMatrix(size_t _rows, size_t _cols,
                  std::vector<double> _value,
                  std::vector<int>    _colIndex,
                  std::vector<int>    _rowIndex);
     explicit SparseMatrix(const Matrix& matrix);
     SparseMatrix(const SparseMatrix& matrix) = default;
     SparseMatrix(size_t _rows, size_t _cols, size_t _elemsCount);

     bool operator== (const SparseMatrix& mat) const&;

     Matrix SparseToMatrix();

     void printDefault();
     void printMatrix();

     friend SparseMatrix SparseMatMul(const SparseMatrix& matrixA, const SparseMatrix& matrixB);
     friend SparseMatrix SparseMatMulOmp(const SparseMatrix& matrixA, const SparseMatrix& matrixB);
};

SparseMatrix SparseMatMul(const SparseMatrix& matrixA, const SparseMatrix& matrixB);
SparseMatrix SparseMatMulOmp(const SparseMatrix& matrixA, const SparseMatrix& matrixB);
Matrix MatMul(const Matrix& matrixA, const Matrix& matrixB);

Matrix generateMatrix(const size_t& rows, const size_t& cols, const size_t& coeff);

void print(const Matrix& matrix);

#endif  // MODULES_TASK_2_SOKOLOV_A_SPARSE_MATRIX_CRS_SPARSE_MATRIX_CRS_OMP_H_
