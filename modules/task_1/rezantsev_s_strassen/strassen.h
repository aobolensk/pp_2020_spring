// Copyright 2020 Rezantsev Sergey
#ifndef MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
#define MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
#include <time.h>
#include <random>
#include <vector>

void splitMatrix(std::vector<double> a, std::vector<double> *a11,
                 std::vector<double> *a22, std::vector<double> *a12,
                 std::vector<double> *a21, int n);
std::vector<double> collectMatrix(std::vector<double> a11,
                                  std::vector<double> a22,
                                  std::vector<double> a12,
                                  std::vector<double> a21, int m);
std::vector<double> strassen(std::vector<double> a, std::vector<double> b,
                             int n);
int checkSize(int n);
std::vector<double> resizeMatrix(std::vector<double> a, int n);
std::vector<double> sumMatrix(std::vector<double> a, std::vector<double> b,
                              int n);
std::vector<double> subtMatrix(std::vector<double> a, std::vector<double> b,
                               int n);
std::vector<double> multMatrix(std::vector<double> a, std::vector<double> b,
                               int n);
bool isEqMatrix(std::vector<double> a, std::vector<double> b, int n);
#endif  // MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
