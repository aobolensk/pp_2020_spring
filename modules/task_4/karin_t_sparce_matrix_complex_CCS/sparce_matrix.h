// Copyright 2020 Karin Timofey
#ifndef MODULES_TASK_4_KARIN_T_SPARCE_MATRIX_COMPLEX_CCS_SPARCE_MATRIX_H_
#define MODULES_TASK_4_KARIN_T_SPARCE_MATRIX_COMPLEX_CCS_SPARCE_MATRIX_H_

#include <vector>
#include <string>
#include <complex>
#include <thread>

struct SparceMatrix {
  int nRow, nCol;
  std::vector<std::complex<int>> val;
  std::vector<int> row_number;
  std::vector<int> point;
  SparceMatrix(int _nCol, int _nRow);
  SparceMatrix(int _nCol, int _nRow, int not_null_count);
  explicit SparceMatrix(std::vector<std::vector<std::complex<int>>>);
  SparceMatrix(int _nCol, int _nRow, std::vector<std::complex<int>> _val,
    std::vector<int> _row_number, std::vector<int> _point);
  SparceMatrix Transpose() const;
  SparceMatrix operator*(const SparceMatrix &MB);
  bool operator==(const SparceMatrix& SP) const;
  void Print();
};

SparceMatrix ParMult(const SparceMatrix& A, const SparceMatrix& B, 
  int th_num = std::thread::hardware_concurrency());
void AtomMult(const SparceMatrix* Atr, const SparceMatrix* B,
  std::vector<std::complex<int>>* res_val,
  std::vector<int>* res_row_num, std::vector<int>* res_point, int start, int end);
std::complex<int> ScalarMult(const SparceMatrix &A, int i, const SparceMatrix &B, int j);

#endif  // MODULES_TASK_4_KARIN_T_SPARCE_MATRIX_COMPLEX_CCS_SPARCE_MATRIX_H_
