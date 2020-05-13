// Copyright 2020 Shashkin Evgeny
#include "../../modules/task_1/shashkin_e_sparse_matrix_multiplication_crs/sparse_matrix_multiplication_crs.h"
#include <vector>

SparseComplexMatrix::SparseComplexMatrix() {
  rows_num = 0;
  cols_num = 0;
}

SparseComplexMatrix::SparseComplexMatrix(int _rows_num, int _cols_num) {
  if (_rows_num < 0)
    throw std::runtime_error("Error! Incorrect numbers of rows!\n");
  if (_cols_num < 0)
    throw std::runtime_error("Error! Incorrect numbers of cols!\n");
  rows_num = _rows_num;
  cols_num = _cols_num;
}

SparseComplexMatrix::SparseComplexMatrix(int _rows_num, int _cols_num, std::vector<std::complex<double>> _values,
  std::vector<int> _col_index, std::vector<int> _row_index) {
  if (_rows_num < 0)
    throw std::runtime_error("Error! Incorrect numbers of rows!\n");
  if (_cols_num < 0)
    throw std::runtime_error("Error! Incorrect numbers of cols!\n");
  rows_num = _rows_num;
  cols_num = _cols_num;
  values = _values;
  col_index = _col_index;
  row_index = _row_index;
}

SparseComplexMatrix::SparseComplexMatrix(const SparseComplexMatrix& sparse_complex_matrix) {
  rows_num = sparse_complex_matrix.rows_num;
  cols_num = sparse_complex_matrix.cols_num;
  values = sparse_complex_matrix.values;
  col_index = sparse_complex_matrix.col_index;
  row_index = sparse_complex_matrix.row_index;
}

std::vector<std::vector<std::complex<double>>> randomMatrix(int _rows_num, int _cols_num) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<std::vector<std::complex<double>>> result(_rows_num);
  for (int i = 0; i < _rows_num; ++i)
    result[i].resize(_cols_num);
  for (int i = 0; i < _rows_num; ++i)
    for (int j = 0; j < _cols_num; ++j) {
      std::complex<double> val(0.0, 0.0);
      result[i][j] = val;
      if (gen() % 10 >= 8) {
        std::complex<double> tmp(static_cast<double>(gen() % 10), static_cast<double>(gen() % 10));
        result[i][j] = tmp;
      }
    }
  return result;
}

SparseComplexMatrix SparseComplexMatrix::matrixToCRS(std::vector<std::vector<std::complex<double>>> matrix) {
  rows_num = matrix.size();
  cols_num = matrix[0].size();
  if (rows_num < 0)
    throw std::runtime_error("Error! Incorrect numbers of rows!\n");
  if (cols_num < 0)
    throw std::runtime_error("Error! Incorrect numbers of cols!\n");
  SparseComplexMatrix result(rows_num, cols_num);
  std::complex<double> empty(0.0, 0.0);
  int tmp = -1;
  int point;
  int count;
  for (int i = 0; i < rows_num; ++i) {
    count = 0;
    point = tmp;
    for (int j = 0; j < cols_num; ++j) {
      if (matrix[i][j] != empty) {
        result.values.push_back(matrix[i][j]);
        result.col_index.push_back(j);
        tmp++;
        count++;
      }
    }
    if (count == 0)
      result.row_index.push_back(point+1);
    else
      result.row_index.push_back(tmp-count+1);
  }
  tmp++;
  result.row_index.push_back(tmp);
  return result;
}

SparseComplexMatrix SparseComplexMatrix::transposeCRS() {
  SparseComplexMatrix result(cols_num, rows_num);
  std::vector<int> rowT_count;
  std::vector<int> row_count;
  std::vector<int> row_idxs;
  int k = 0;
  result.row_index.push_back(0);
  for (int i = 0; i < rows_num; ++i) {
    row_count.push_back(row_index[i + 1] - row_index[i]);
    for (int j = 0; j < row_count[i]; ++j)
      row_idxs.push_back(i);
  }
  for (int i = 0; i < cols_num; ++i) {
    for (unsigned j = 0; j < values.size(); ++j) {
      if (col_index[j] == i) {
        result.values.push_back(values[j]);
        result.col_index.push_back(row_idxs[j]);
        k++;
      }
    }
    rowT_count.push_back(k);
    k = 0;
    result.row_index.push_back(result.row_index[i] + rowT_count[i]);
  }
  return result;
}

bool SparseComplexMatrix::operator==(const SparseComplexMatrix& mat) const& {
  if (rows_num != mat.rows_num || cols_num != mat.cols_num ||
    values != mat.values || col_index != col_index || row_index != mat.row_index) {
    return false;
  } else {
    for (unsigned i = 0; i < values.size(); ++i) {
      if (values[i].real() != mat.values[i].real() || values[i].imag() != mat.values[i].imag())
        return false;
    }
    return true;
  }
}

SparseComplexMatrix SparseComplexMatrix::operator*(const SparseComplexMatrix& mat) const& {
  SparseComplexMatrix result(rows_num, mat.cols_num);
  SparseComplexMatrix tmp;
  tmp = mat;
  tmp = tmp.transposeCRS();
  int not_zero_vals = 0;
  if (cols_num != tmp.cols_num)
    throw std::runtime_error("Error! Incorrect numbers of cols!\n");
  result.row_index.push_back(0);
  for (unsigned i = 1; i < row_index.size(); ++i) {
    for (unsigned j = 1; j < tmp.row_index.size(); ++j) {
      std::complex<double> s = 0;
      int iter1 = row_index[i - 1];
      int iter2 = tmp.row_index[j - 1];
      while ((iter1 < row_index[i]) && (iter2 < tmp.row_index[j])) {
        if (col_index[iter1] == tmp.col_index[iter2]) {
          s += values[iter1] * tmp.values[iter2];
          iter1++;
          iter2++;
        } else {
          if (col_index[iter1] < tmp.col_index[iter2]) {
            iter1++;
          } else {
            iter2++;
          }
        }
      }
      if (s.real() != 0.0 || s.imag() != 0.0) {
        result.values.push_back(s);
        result.col_index.push_back(j - 1);
        not_zero_vals++;
      }
    }
    result.row_index.push_back(not_zero_vals);
  }
  return result;
}

void SparseComplexMatrix::printCRS() {
  for (unsigned i = 0; i < values.size(); ++i)
    std::cout << values[i] << " ";
  std::cout << "\n";
  for (unsigned i = 0; i < col_index.size(); ++i)
    std::cout << col_index[i] << " ";
  std::cout << "\n";
  for (unsigned i = 0; i < row_index.size(); ++i)
    std::cout << row_index[i] << " ";
  std::cout << "\n";
}

void print(std::vector<std::vector<std::complex<double>>> matrix) {
  int rows = matrix.size();
  int cols = matrix[0].size();
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j)
      std::cout << matrix[i][j] << " ";
    std::cout << "\n";
  }
}
