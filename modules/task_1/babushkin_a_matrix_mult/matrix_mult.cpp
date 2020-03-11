// Copyright 2020 Babushkin Alexey

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "./matrix_mult.h"

using namespace mtrxmult;

Matrix Matrix::multiply(const Matrix &right) {
  if (right.m_data.size() == 0) {
    throw new std::invalid_argument("Matrices must not be empty.");
  }

  if (m_rows != right.m_cols) {
    throw new std::invalid_argument(
        "Right matrix must contain left matrix rows number of columns");
  }

  return Matrix();
}

// Matrix Matrix::multiply(const Matrix &right) { Matrix result; }