// Copyright 2020 Shashkin Evgeny
#ifndef MODULES_TASK_2_SHASHKIN_E_SPARSE_MATRIX_MULTIPLICATION_CRS_SPARSE_MATRIX_MULTIPLICATION_CRS_H_
#define MODULES_TASK_2_SHASHKIN_E_SPARSE_MATRIX_MULTIPLICATION_CRS_SPARSE_MATRIX_MULTIPLICATION_CRS_H_

#include <iostream>
#include <vector>
#include <complex>
#include <random>
#include <ctime>
#include <algorithm>

class SparseComplexMatrix {
 private:
  int rows_num;
  int cols_num;

  std::vector<std::complex<double>> values;
  std::vector<int> col_index;
  std::vector<int> row_index;
 public:
  SparseComplexMatrix();
  SparseComplexMatrix(int _rows_num, int _cols_num);
  SparseComplexMatrix(int _rows_num, int _cols_num, std::vector<std::complex<double>> _values,
    std::vector<int> _col_index, std::vector<int> _row_index);
  SparseComplexMatrix(const SparseComplexMatrix& sparse_complex_matrix);
  bool operator==(const SparseComplexMatrix& mat) const&;
  SparseComplexMatrix operator*(const SparseComplexMatrix& mat) const&;
  SparseComplexMatrix crsParallelMult(const SparseComplexMatrix& mat) const&;
  SparseComplexMatrix matrixToCRS(std::vector<std::vector<std::complex<double>>> matrix);
  SparseComplexMatrix transposeCRS();
  void printCRS();
};

std::vector<std::vector<std::complex<double>>> randomMatrix(int _rows_num, int _cols_num, double percent);
void print(std::vector<std::vector<std::complex<double>>> matrix);
#endif  // MODULES_TASK_2_SHASHKIN_E_SPARSE_MATRIX_MULTIPLICATION_CRS_SPARSE_MATRIX_MULTIPLICATION_CRS_H_
