// Copyright 2020 Babushkin Alexey

#include "../../../modules/task_1/babushkin_a_matrix_mult/matrix_mult.h"

#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>
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

bool Matrix::equals(const Matrix &other) {
  if (m_row_storage != other.m_row_storage || m_rows != other.m_rows ||
      m_cols != other.m_cols || m_data.size() != other.m_data.size()) {
    return false;
  }

  bool equal = true;
  auto eps = 1e-6;

  for (uint32_t i = 0; i < m_data.size(); i++) {
    if (std::abs(m_data.at(i) - other.m_data.at(i)) > eps) {
      equal = false;
      break;
    }
  }

  return equal;
}

void Matrix::column_storage() {
  if (m_row_storage == true) {
    std::vector<double> column_storage_data;
    // copy matrix columnwise
    for (auto j = 0; j < m_cols; j++) {
      for (auto i = 0; i < m_rows; i++) {
        column_storage_data.push_back(m_data.at(i * m_cols + j));
      }
    }

    m_data = column_storage_data;
    m_row_storage = false;
  } else {
    throw new std::logic_error("Already stored columnwise");
  }
}

void Matrix::row_storage() {
  if (m_row_storage == false) {
    m_row_storage = true;
    column_storage();
    m_row_storage = true;
  } else {
    throw new std::logic_error("Already stored rowwise");
  }
}

template <class InputIt, class T>
void shift_left(InputIt first, InputIt last, const T &value) {
  for (auto i = first; i < last - value; i++) {
    auto current = i;

    for (auto j = 0; j < value; j++) {
      if (current == first) {
        std::iter_swap(current, last - 1);
        current = last - 1;
      } else {
        std::iter_swap(current, current - 1);
        current--;
      }
    }
  }
}

template <class InputIt, class T>
void shift_right(InputIt first, InputIt last, const T &value) {
  for (auto i = last - 1; i >= first + value; i--) {
    auto current = i;

    for (auto j = 0; j < value; j++) {
      if (last - current - 2 < 0) {
        std::iter_swap(first, current);
        current = first;
      } else {
        std::iter_swap(current, current + 1);
        current++;
      }
    }
  }
}

Matrix multiply(const Matrix left, const Matrix right) {
  if (right.m_data.size() == 0 || left.m_data.size() == 0) {
    throw new std::invalid_argument("Matrices must not be empty");
    return Matrix();
  }

  if (right.m_rows != left.m_cols) {
    throw new std::invalid_argument(
        "Right matrix must contain left matrix rows number of columns");
    return Matrix();
  }

  std::vector<double> result_vector;

  for (auto i = 0; i < left.m_rows; i++) {
    for (auto j = 0; j < right.m_cols; j++) {
      result_vector.push_back(0);
      for (auto k = 0; k < left.m_cols; k++) {
        result_vector.back() += left.m_data.at(i * left.m_cols + k) *
                                right.m_data.at(k * right.m_cols + j);
      }
    }
  }

  return Matrix(result_vector, left.m_rows, right.m_cols);
}

Matrix multiply_cannon(Matrix left, Matrix right) {
  if (right.m_data.size() == 0 || left.m_data.size() == 0) {
    throw new std::invalid_argument("Matrices must not be empty");
    return Matrix();
  }

  if (right.m_rows != left.m_cols) {
    throw new std::invalid_argument(
        "Right matrix must contain left matrix rows number of columns");
    return Matrix();
  }

  if (right.m_row_storage != false) {
    throw new std::invalid_argument(
        "Right matrix must be stored columnwise, call column_storage() on it"
        "first");
    return Matrix();
  }

  // left-circular-shift left matrix i-row by i positions
  for (auto i = 0; i < left.m_rows; i++) {
    shift_left(left.m_data.begin() + i * left.m_cols,
               left.m_data.begin() + i * left.m_cols + left.m_cols, i);
  }

  // Up-circular-shift right matrix i-column by i positions
  for (auto i = 0; i < right.m_cols; i++) {
    shift_left(right.m_data.begin() + i * right.m_rows,
               right.m_data.begin() + i * right.m_rows + right.m_cols, i);
  }

  std::vector<double> result_vec;
  result_vec.resize(left.m_rows * right.m_cols, 0);

  for (auto k = 0; k < left.m_rows; k++) {
    for (auto i = 0; i < left.m_rows; i++) {
      for (auto j = 0; j < right.m_cols; j++) {
        result_vec.at(i * right.m_cols + j) +=
            left.m_data.at(i * left.m_cols + j) *
            right.m_data.at(j * right.m_rows + i);
      }

      shift_left(left.m_data.begin() + i * left.m_cols,
                 left.m_data.begin() + i * left.m_cols + left.m_cols, 1);
    }

    for (auto i = 0; i < right.m_cols; i++) {
      shift_left(right.m_data.begin() + i * right.m_rows,
                 right.m_data.begin() + i * right.m_rows + right.m_cols, 1);
    }
  }

  return Matrix(result_vec, left.m_rows, right.m_cols);
}

Matrix random_matrix(const int rows, const int columns) {
  std::mt19937 gen;
  std::random_device rand_device;
  gen.seed(rand_device());

  std::uniform_real_distribution<double> dist(0.0, 50.0);

  std::vector<double> data;
  data.resize(rows * columns);

  std::generate(data.begin(), data.end() - 1, [&]() { return dist(gen); });

  return Matrix(data, rows, columns);
}

}  // namespace mtrxmult
