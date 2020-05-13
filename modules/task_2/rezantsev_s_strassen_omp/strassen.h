// Copyright 2020 Rezantsev Sergey
#ifndef MODULES_TASK_2_REZANTSEV_S_STRASSEN_OMP_STRASSEN_H_
#define MODULES_TASK_2_REZANTSEV_S_STRASSEN_OMP_STRASSEN_H_
#include <omp.h>
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
std::vector<double> sumMatrix(std::vector<double> a, std::vector<double> b,
                              int n);
std::vector<double> subtMatrix(std::vector<double> a, std::vector<double> b,
                               int n);
std::vector<double> multMatrix(std::vector<double> a, std::vector<double> b,
                               int n);
int checkSize(int n);
std::vector<double> resizeMatrix(std::vector<double> a, int n);


void sumMatrix(const std::vector<double> &a, const std::vector<double> &b,
               std::vector<double> *c);
void subtMatrix(const std::vector<double> &a, const std::vector<double> &b,
                std::vector<double> *c);
void multMatrix(const std::vector<double> &a, const std::vector<double> &b,
                std::vector<double> *c, int n);
bool isEqMatrix(std::vector<double> a, std::vector<double> b, int n);
void strassen_omp(const std::vector<double> &a, const std::vector<double> &b,
              std::vector<double> *result);
#endif  // MODULES_TASK_2_REZANTSEV_S_STRASSEN_OMP_STRASSEN_H_
