// Copyright 2020 Golubeva Anna
#ifndef MODULES_TASK_1_GOLUBEVA_A_FOX_MULT_FOX_H_
#define MODULES_TASK_1_GOLUBEVA_A_FOX_MULT_FOX_H_

#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix simpleMult(const Matrix& A, const Matrix& B);
Matrix foxMult(const Matrix& A, const Matrix& B, const int &blockSize);
Matrix randMatrix(const int& n);

#endif  // MODULES_TASK_1_GOLUBEVA_A_FOX_MULT_FOX_H_
