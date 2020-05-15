// Copyright 2020 Babushkin Alexey

#include "../../../modules/task_3/babushkin_a_matrix_mult/matrix_mult.h"

#include <tbb/tbb.h>

#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace mtrxmult {
std::string Matrix::to_string() {
  std::string matrix("Matrix(");

  matrix += std::to_string(m_rows) + ", " + std::to_string(m_cols) + ")[\n ";
  // insert matrix contents into resulting string
  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_cols; j++) {
      matrix += std::to_string(m_data.at(i * m_rows + j)) + " ";
    }
    matrix += "\n";
  }
  // delete extra comma
  matrix.erase(matrix.size() - 2, 2);
  matrix += "\n]";

  return matrix;
}

bool operator==(const Matrix &a, const Matrix &b) {
  if (a.m_rows != b.m_rows || a.m_cols != b.m_cols ||
      a.m_data.size() != b.m_data.size()) {
    return false;
  }

  bool equal = true;
  auto eps = 1e-6;

  for (uint32_t i = 0; i < a.m_data.size(); i++) {
    if (std::abs(a.m_data.at(i) - b.m_data.at(i)) > eps) {
      equal = false;
      break;
    }
  }

  return equal;
}

bool operator!=(const Matrix &a, const Matrix &b) { return !(a == b); }

void Matrix::shift_left(const int block_size, const bool skew) {
  shift(block_size, skew, left);
}

void Matrix::shift_up(const int block_size, const bool skew) {
  shift(block_size, skew, up);
}

void Matrix::shift(const int block_size, const bool skew, direction d) {
  std::vector<double> data(m_rows);

  for (int i = 0, j = 0; i < m_rows; i += block_size, j++) {
    for (int k = i; k < (i + block_size); k++) {
      int step = skew ? j * block_size : block_size;

      for (int m = 0; m < m_cols; m++) {
        if (d == up) {
          data.at(m) = m_data.at(((m + step) % m_cols) * m_cols + k);
        } else {
          data.at(m) = m_data.at(k * m_cols + ((m + step) % m_cols));
        }
      }

      for (int m = 0; m < m_cols; m++) {
        if (d == up) {
          m_data.at(m * m_cols + k) = data.at(m);
        } else {
          m_data.at(k * m_cols + m) = data.at(m);
        }
      }
    }
  }
}

struct Mult {
  const Matrix &left;
  const Matrix &right;

  std::vector<double> &result;

  Mult(const Matrix &t_left, const Matrix &t_right, std::vector<double> &res)
      : left(t_left), right(t_right), result(res) {}

  void operator()(const tbb::blocked_range<int> &r) const {
    result.resize(left.get_rows() * right.get_cols());

    for (auto i = r.begin(); i != r.end(); i++) {
      for (auto j = 0; j < right.get_cols(); j++) {
        for (auto k = 0; k < left.get_cols(); k++) {
          result.at(i * right.get_cols() + j) += left.at(i, k) * right.at(k, j);
        }
      }
    }
  }
};

Matrix multiply(const Matrix &left, const Matrix &right,
                const bool isParallel) {
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

  if (isParallel) {
    tbb::parallel_for(tbb::blocked_range<int>(0, right.m_rows),
                      Mult(left, right, result_vector));
  } else {
    for (auto i = 0; i < left.m_rows; i++) {
      for (auto j = 0; j < right.m_cols; j++) {
        result_vector.push_back(0);
        double result = 0;

        for (auto k = 0; k < left.m_cols; k++) {
          result += left.at(i, k) * right.at(k, j);
        }

        result_vector.back() += result;
      }
    }
  }

  return Matrix(result_vector, left.m_rows, right.m_cols);
}

Matrix random_matrix(const int rows, const int columns) {
  std::mt19937 gen;
  std::random_device rand_device;
  gen.seed(rand_device());

  std::uniform_real_distribution<double> dist(0.0, 50.0);

  std::vector<double> data;
  data.resize(rows * columns);

  std::generate(data.begin(), data.end(), [&]() { return dist(gen); });

  return Matrix(data, rows, columns);
}

}  // namespace mtrxmult