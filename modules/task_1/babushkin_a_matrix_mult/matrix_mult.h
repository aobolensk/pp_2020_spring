// Copyright 2020 Babushkin Alexey

#include <stdexcept>
#include <string>
#include <vector>

#ifndef MODULES_TASK_1_BABUSHKIN_A_MATRIX_MULT_MATRIX_MULT_H_
#define MODULES_TASK_1_BABUSHKIN_A_MATRIX_MULT_MATRIX_MULT_H_

namespace mtrxmult {
class Matrix {
 private:
  int m_rows;
  int m_cols;
  std::vector<double> m_data;
  bool m_row_storage;

 public:
  Matrix() : m_rows(0), m_cols(0), m_data({}), m_row_storage(true) {}

  Matrix(const std::vector<double> &t_data, const int t_rows, const int t_cols)
      : m_rows(t_rows), m_cols(t_cols), m_data(t_data), m_row_storage(true) {}

  int get_rows() const noexcept { return m_rows; }
  int get_cols() const noexcept { return m_cols; }
  unsigned get_size() const noexcept { return (unsigned)m_data.size(); }

  std::vector<double> get_data() { return std::vector<double>(m_data); }

  bool is_rowwise_stored() { return m_row_storage; }

  void resize(const int t_rows, const int t_cols) {
    m_data.resize(t_rows * t_cols);
    m_rows = t_rows;
    m_cols = t_cols;
  }

  std::string to_string();
  bool equals(const Matrix &);

  void column_storage();
  void row_storage();

  template <class InputIt, class T>
  friend void shift_left(InputIt first, InputIt last, const T &value);

  template <class InputIt, class T>
  friend void shift_right(InputIt first, InputIt last, const T &value);

  friend Matrix multiply(const Matrix left, const Matrix right);

  friend Matrix multiply_cannon(Matrix left, Matrix right);
};

Matrix random_matrix(const int rows, const int columns);

template <class InputIt, class T>
void shift_left(InputIt first, InputIt last, const T &value);

template <class InputIt, class T>
void shift_right(InputIt first, InputIt last, const T &value);

Matrix multiply(const Matrix left, const Matrix right);

Matrix multiply_cannon(Matrix left, Matrix right);

}  // namespace mtrxmult

#endif  // MODULES_TASK_1_BABUSHKIN_A_MATRIX_MULT_MATRIX_MULT_H_
