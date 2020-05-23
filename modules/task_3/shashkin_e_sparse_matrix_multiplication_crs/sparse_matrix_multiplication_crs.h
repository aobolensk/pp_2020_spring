// Copyright 2020 Shashkin Evgeny
#ifndef MODULES_TASK_3_SHASHKIN_E_SPARSE_MATRIX_MULTIPLICATION_CRS_SPARSE_MATRIX_MULTIPLICATION_CRS_H_
#define MODULES_TASK_3_SHASHKIN_E_SPARSE_MATRIX_MULTIPLICATION_CRS_SPARSE_MATRIX_MULTIPLICATION_CRS_H_

#include <tbb/tbb.h>
#include <iostream>
#include <vector>
#include <complex>
#include <random>
#include <ctime>
#include <algorithm>

class SparseComplexMatrix {
 public:
  int rows_num;
  int cols_num;

  std::vector<std::complex<double>> values;
  std::vector<int> col_index;
  std::vector<int> row_index;

  SparseComplexMatrix();
  SparseComplexMatrix(int _rows_num, int _cols_num);
  SparseComplexMatrix(int _rows_num, int _cols_num, std::vector<std::complex<double>> _values,
    std::vector<int> _col_index, std::vector<int> _row_index);
  SparseComplexMatrix(const SparseComplexMatrix& sparse_complex_matrix);
  int getValuesNum();
  bool operator==(const SparseComplexMatrix& mat) const&;
  SparseComplexMatrix operator*(const SparseComplexMatrix& mat) const&;
  SparseComplexMatrix crsParallelMult(const SparseComplexMatrix& mat) const&;
  SparseComplexMatrix matrixToCRS(std::vector<std::vector<std::complex<double>>> matrix);
  SparseComplexMatrix transposeCRS();
  void printCRS();
};

class MatrixMultiplicator {
 private:
  const SparseComplexMatrix& matA;
  const SparseComplexMatrix& matB;

  std::vector<std::complex<double>>& vals;
  std::vector<int>& cols;

  const unsigned& i;
  tbb::atomic<int>& not_zero_vals;
 public:
  MatrixMultiplicator(const SparseComplexMatrix& _matA, const SparseComplexMatrix& _matB,
    std::vector<std::complex<double>>* _vals, std::vector<int>* _cols, const unsigned& _i,
    tbb::atomic<int>& _not_zero_vals) : matA(_matA), matB(_matB), vals(*_vals), cols(*_cols), i(_i),
    not_zero_vals(_not_zero_vals) {}

  void operator()(const tbb::blocked_range<int>& r) const;
};

std::vector<std::vector<std::complex<double>>> randomMatrix(int _rows_num, int _cols_num, double percent);
void print(std::vector<std::vector<std::complex<double>>> matrix);
#endif  // MODULES_TASK_3_SHASHKIN_E_SPARSE_MATRIX_MULTIPLICATION_CRS_SPARSE_MATRIX_MULTIPLICATION_CRS_H_
