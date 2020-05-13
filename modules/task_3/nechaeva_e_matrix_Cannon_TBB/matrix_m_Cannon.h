// Copyright 2020 Nechaeva Ekaterina
#ifndef MODULES_TASK_3_NECHAEVA_E_MATRIX_CANNON_TBB_MATRIX_M_CANNON_H_
#define MODULES_TASK_3_NECHAEVA_E_MATRIX_CANNON_TBB_MATRIX_M_CANNON_H_

#include <vector>
#include <complex>
#include <iostream>
#include <cmath>

using matrix = std::vector<std::vector<double>>;

matrix RandomMatrix(const int n);

matrix NaiveMulti(const matrix &A, const matrix &B);
matrix BlockMulti(const matrix &A, const matrix &B, const int &blockSize);
matrix AlgorithmCannonTBB(const matrix &A, const matrix &B);

bool CompareMatrix(const matrix &A, const matrix &B);
bool CompareValues(const double &a, const double &b);

#endif  // MODULES_TASK_3_NECHAEVA_E_MATRIX_CANNON_TBB_MATRIX_M_CANNON_H_
