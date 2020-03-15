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
    int rows;
    int cols;
    std::vector<double> value;
    std::vector<int> colIndex;  // Column numbers for each item
    std::vector<int> rowIndex;  // Index of the beginning of each line
 public:
     SparseMatrix() : rows(0), cols(0) {}
     SparseMatrix(int _rows, int _cols,
                  std::vector<double> _value,
                  std::vector<int>    _colIndex,
                  std::vector<int>    _rowIndex);
     explicit SparseMatrix(const Matrix& matrix);
     SparseMatrix(const SparseMatrix& matrix) = default;
     SparseMatrix(int _rows, int _cols, int _elemsCount);

     bool operator== (const SparseMatrix& mat) const&;

     Matrix SparseToMatrix();

     void printDefault();
     void printMatrix();

     friend SparseMatrix SparseMatMul(const SparseMatrix& matrixA, const SparseMatrix& matrixB);
};

SparseMatrix SparseMatMul(const SparseMatrix& matrixA, const SparseMatrix& matrixB);
Matrix MatMul(const Matrix& matrixA, const Matrix& matrixB);

Matrix generateMatrix(const int& rows, const int& cols, const int& coeff);

void print(const Matrix& matrix);

#endif  // MODULES_TASK_1_SOKOLOV_A_SPARSE_MATRIX_STRING_CRS_SPARSE_MATRIX_STRING_CRS_H_
