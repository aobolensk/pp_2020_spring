// Copyright 2020 Babushkin Alexey

#include "../../../modules/task_2/babushkin_a_matrix_mult/matrix_mult.h"

#include <omp.h>

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

  for (auto i = 0; i < left.m_rows; i++) {
    for (auto j = 0; j < right.m_cols; j++) {
      result_vector.push_back(0);
      double result = 0;

      if (isParallel) {
#pragma omp parallel for reduction(+ : result)
        for (auto k = 0; k < left.m_cols; k++) {
          result += left.m_data.at(i * left.m_cols + k) *
                    right.m_data.at(k * right.m_cols + j);
        }
      } else {
        for (auto k = 0; k < left.m_cols; k++) {
          result += left.m_data.at(i * left.m_cols + k) *
                    right.m_data.at(k * right.m_cols + j);
        }
      }
      result_vector.back() += result;
    }
  }

  return Matrix(result_vector, left.m_rows, right.m_cols);
}

Matrix multiply_cannon(Matrix *left, Matrix *right) {
  if (right->m_data.size() == 0 || left->m_data.size() == 0) {
    throw new std::invalid_argument("Matrices must not be empty");
    return Matrix();
  }

  if (right->m_rows != left->m_cols) {
    throw new std::invalid_argument(
        "Right matrix must contain left matrix rows number of columns");
    return Matrix();
  }

  if (right->m_rows != right->m_cols) {
    throw new std::invalid_argument("Matrices must be homogenious");
    return Matrix();
  }

  int size = omp_get_max_threads();
  if (size < 4) {
    return multiply(*left, *right, PARALLEL);
  }

  int sqrt_size = std::sqrt(size);
  int block_size = left->m_cols / sqrt_size;

  // left-circular-shift left matrix i-row by i positions
  left->shift_left(block_size, true);
  // Up-circular-shift right matrix i-column by i positions
  right->shift_up(block_size, true);

  std::vector<double> result(left->m_data.size());

  for (int iter = 0; iter < sqrt_size; iter++) {
#pragma omp parallel
    {
      int rank = omp_get_thread_num();
      int row_start = (rank / sqrt_size) * block_size;
      int row_end = row_start + block_size;

      int col_start = (rank % sqrt_size) * block_size;
      int col_end = col_start + block_size;

      std::vector<double> left_block(block_size * block_size);
      std::vector<double> right_block(block_size * block_size);
      std::vector<double> res_block(block_size * block_size);

      // copy blocks
      for (int r = row_start, l = 0; r < row_end; r++, l++) {
        for (int c = col_start, m = 0; c < col_end; c++, m++) {
          left_block.at(l * block_size + m) =
              left->m_data.at(r * left->m_cols + c);
          right_block.at(l * block_size + m) =
              right->m_data.at(r * right->m_cols + c);
          res_block.at(l * block_size + m) = result.at(r * right->m_cols + c);
        }
      }

      // multiply blocks
      for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < block_size; j++) {
          for (int k = 0; k < block_size; k++) {
            res_block.at(i * block_size + j) +=
                left_block.at(i * block_size + k) *
                right_block.at(k * block_size + j);
          }
        }
      }

      // write blocks back to the result
      for (int r = row_start, l = 0; r < row_end; r++, l++) {
        for (int c = col_start, m = 0; c < col_end; c++, m++) {
          result.at(r * right->m_cols + c) = res_block.at(l * block_size + m);
        }
      }
    }

    left->shift_left(block_size, false);
    right->shift_up(block_size, false);
  }

  return Matrix(result, left->m_rows, left->m_cols);
}  // namespace mtrxmult

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
