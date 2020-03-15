// Copyright 2020 Karin Timofey
#ifndef MODULES_TASK1_KARIN_T_SPARCE_MATRIX_COMPLEX_CCS_H_
#define MODULES_TASK1_KARIN_T_SPARCE_MATRIX_COMPLEX_CCS_H_

#include <vector>
#include <string>
#include <complex>

struct SparceMatrix {
  int nRow, nCol;
  std::vector<std::complex<int>> val;
  std::vector<int> row_number;
  std::vector<int> point;

  SparceMatrix(int _nCol, int _nRow, int not_null_count = 0);
  SparceMatrix(std::vector<std::vector<std::complex<int>>>);
  SparceMatrix(int _n—ol, int _nRow, std::vector<std::complex<int>> _val, std::vector<int> _row_number, 
               std::vector<int> _point);
  SparceMatrix Transpose();
  SparceMatrix operator*(const SparceMatrix &MB);
  void Print();
  int colCount(int col);
};

#endif  // MODULES_TASK1_KARIN_T_SPARCE_MATRIX_COMPLEX_CCS_H_
