// Copyright 2020 Babushkin Alexey

#include <stdexcept>
#include <string>
#include <vector>

#ifndef MODULES_TASK_2_BABUSHKIN_A_MATRIX_MULT_MATRIX_MULT_H_
#define MODULES_TASK_2_BABUSHKIN_A_MATRIX_MULT_MATRIX_MULT_H_

#define SEQUENTIAL false
#define PARALLEL true

namespace mtrxmult {
class Matrix {
 private:
  int m_rows;
  int m_cols;

  std::vector<double> m_data;

 public:
  Matrix() : m_rows(0), m_cols(0), m_data({}) {}

  Matrix(const std::vector<double> &t_data, const int t_rows, const int t_cols)
      : m_rows(t_rows), m_cols(t_cols), m_data(t_data) {}

  int get_rows() const noexcept { return m_rows; }
  int get_cols() const noexcept { return m_cols; }
  unsigned get_size() const noexcept { return (unsigned)m_data.size(); }

  std::vector<double> get_data() { return std::vector<double>(m_data); }

  void resize(const int t_rows, const int t_cols) {
    m_data.resize(t_rows * t_cols);
    m_rows = t_rows;
    m_cols = t_cols;
  }

  std::string to_string();
  bool equals(const Matrix &);

  void shift_left(const int block_size, const bool sqew);
  void shift_up(const int block_size, const bool sqew);

  friend Matrix multiply(const Matrix &left, const Matrix &right,
                         const bool isParallel);
  friend Matrix multiply_cannon(Matrix *left, Matrix *right);
};

Matrix random_matrix(const int rows, const int columns);

Matrix multiply(const Matrix &left, const Matrix &right, const bool isParallel);
Matrix multiply_cannon(Matrix *left, Matrix *right);

}  // namespace mtrxmult

#endif  // MODULES_TASK_2_BABUSHKIN_A_MATRIX_MULT_MATRIX_MULT_H_
