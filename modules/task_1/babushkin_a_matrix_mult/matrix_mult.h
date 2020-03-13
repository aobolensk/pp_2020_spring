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

 public:
  Matrix() : m_rows(0), m_cols(0), m_data({}) {}
  Matrix(const std::vector<double> &t_data, const int t_rows, const int t_cols)
      : m_rows(t_rows), m_cols(t_cols), m_data(t_data) {}

  int get_rows() const noexcept { return m_rows; }
  int get_cols() const noexcept { return m_cols; }
  unsigned get_size() const noexcept { return (unsigned)m_data.size(); }
  std::vector<double> get_data() { return std::vector<double>(m_data); }

  void resize(int t_rows, int t_cols) {
    m_data.resize(t_rows * t_cols);
    m_rows = t_rows;
    m_cols = t_cols;
  }

  std::string to_string();

  Matrix multiply(const Matrix &);
};

}  // namespace mtrxmult

#endif  // MODULES_TASK_1_BABUSHKIN_A_MATRIX_MULT_MATRIX_MULT_H_
