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
        values.push_back(matrix[i][j]);
        col_index.push_back(j);
        tmp++;
        count++;
      }
    }
    if (count == 0)
      row_index.push_back(point+1);
    else
      row_index.push_back(tmp-count+1);
  }
  tmp++;
  row_index.push_back(tmp);
  return result;
}

SparseComplexMatrix SparseComplexMatrix::transpose() {
  SparseComplexMatrix result(cols_num, rows_num);
  std::vector<std::vector<int>> idx(cols_num);
  std::vector<std::vector<std::complex<double>>> vals(cols_num);
  for (unsigned i = 1; i < row_index.size(); ++i)
    for (int j = row_index[i - 1]; j < row_index[i]; ++j) {
      idx[col_index[j]].push_back(i - 1);
      vals[col_index[j]].push_back(values[j]);
    }
  int size = 0;
  result.row_index.push_back(0);
  for (int i = 0; i < cols_num; ++i) {
    for (unsigned j = 0; j < idx[i].size(); ++j) {
      result.values.push_back(vals[i][j]);
      result.col_index.push_back(idx[i][j]);
    }
    size += idx[i].size();
    result.row_index.push_back(size);
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
  SparseComplexMatrix result(cols_num, mat.cols_num);
  int not_zero_vals = 0;
  if (cols_num != mat.cols_num)
    throw std::runtime_error("Error! Incorrect numbers of cols!\n");
  result.row_index.push_back(0);
  for (unsigned i = 1; i < row_index.size(); ++i) {
    std::vector<std::complex<double>> vec;
    std::vector<int> cols;
    for (unsigned j = 1; j < mat.row_index.size(); ++j) {
      std::complex<double> sum = 0;
      int iter1 = row_index[i - 1];
      int iter2 = mat.row_index[j - 1];
      while ((iter1 < row_index[i]) && (iter2 < mat.row_index[j])) {
        if (col_index[iter1] == mat.col_index[iter2]) {
          sum += values[iter1++] * mat.values[iter2++];
        } else {
          if (col_index[iter1] < mat.col_index[iter2]) {
            iter1++;
          } else {
            iter2++;
          }
        }
      }
      if (sum.real() != 0.0 || sum.imag() != 0.0) {
        vec.push_back(sum);
        cols.push_back(j - 1);
        not_zero_vals++;
      }
    }
    for (unsigned i = 0; i < vec.size(); ++i)
      result.values.push_back(vec[i]);
    for (unsigned i = 0; i < cols.size(); ++i)
      result.col_index.push_back(cols[i]);
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
