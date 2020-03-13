// Copyright 2020 Babushkin Alexey

#include "../../../modules/task_1/babushkin_a_matrix_mult/matrix_mult.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace mtrxmult {
std::string Matrix::to_string() {
  std::string matrix("Matrix(");

  matrix += std::to_string(m_rows) + ", " + std::to_string(m_cols) + ")[ ";
  // insert matrix contents into resulting string
  for (auto elem : m_data) {
    matrix += std::to_string(elem) + ", ";
  }
  // delete extra comma
  matrix.erase(matrix.size() - 2, 2);
  matrix += " ]";

  return matrix;
}

Matrix Matrix::multiply(const Matrix &right) {
  if (right.m_data.size() == 0) {
    throw new std::invalid_argument("Matrices must not be empty.");
    return Matrix();
  }

  if (right.m_rows != m_cols) {
    throw new std::invalid_argument(
        "Right matrix must contain left matrix rows number of columns");
    return Matrix();
  }

  std::vector<double> result_vector;

  for (auto i = 0; i < m_rows; i++) {
    for (auto j = 0; j < right.m_cols; j++) {
      result_vector.push_back(0);
      for (auto k = 0; k < m_cols; k++) {
        result_vector.back() +=
            m_data.at(i * m_cols + k) * right.m_data.at(k * right.m_cols + j);
      }
    }
  }

  return Matrix(result_vector, m_rows, right.m_cols);
}
}  // namespace mtrxmult
