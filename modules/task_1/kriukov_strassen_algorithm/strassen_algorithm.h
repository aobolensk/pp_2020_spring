// Copyright 2020 Kriukov Dmitry
#ifndef MODULES_TASK_1_KRIUKOV_STRASSEN_ALGORITHM_H_
#define MODULES_TASK_1_KRIUKOV_STRASSEN_ALGORITHM_H_

#include <vector>

std::vector<double> getRandomMatrix(int  sz);
std::vector<double> regularMultiplication(std::vector<double> &a, std::vector<double> &b);
std::vector<double> strassenMultiplication(std::vector<double> &a, std::vector<double> &b);
std::vector<double> regularSum(std::vector<double> &a, std::vector<double> &b, int sz);
void splitMatrix(std::vector<double> &mtx, std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, std::vector<double> &d, int size);
void mergeMatrix(std::vector<double> &mtx, std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, std::vector<double> &d, int size);
std::vector<double> toPowerOfTwoSize(std::vector<double> &mtx);

#endif  // MODULES_TASK_1_KRIUKOV_STRASSEN_ALGORITHM_H_
