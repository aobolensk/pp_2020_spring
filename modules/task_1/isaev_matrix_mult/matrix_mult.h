// Copyright 2020 Isaev Ilya
#ifndef MODULES_TASK_1_ISAEV_MATRIX_MULT_MATRIX_MULT_H_
#define MODULES_TASK_1_ISAEV_MATRIX_MULT_MATRIX_MULT_H_

#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix getRandomMatrix(const int& n);
Matrix naiveMultiplication(const Matrix& mat1, const Matrix& mat2);
Matrix blockMultiplication(const Matrix& mat1, const Matrix& mat2);
bool isSquared(const Matrix& mat);
bool matrixComparison(const Matrix& mat1, const Matrix& mat2);
bool doubleComparison(const double& a, const double& b);

#endif  // MODULES_TASK_1_ISAEV_MATRIX_MULT_MATRIX_MULT_H_
