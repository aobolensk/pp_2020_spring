// Copyright 2020 Isaev Ilya
#ifndef MODULES_TASK_1_ISAEV_MATRIX_MULT_MATRIX_MULT_H_
#define MODULES_TASK_1_ISAEV_MATRIX_MULT_MATRIX_MULT_H_

#include <vector>

std::vector<std::vector<double> > getRandomMatrix(const int& n, const int& m);
std::vector<std::vector<double> > operator*(const std::vector<std::vector<double> >& mat1,
                                            const std::vector<std::vector<double> >& mat2);
bool matrixComparison(const std::vector<std::vector<double> >& mat1, const std::vector<std::vector<double> >& mat2);
bool doubleComparison(const double& a, const double& b);

#endif // MODULES_TASK_1_ISAEV_MATRIX_MULT_MATRIX_MULT_H_