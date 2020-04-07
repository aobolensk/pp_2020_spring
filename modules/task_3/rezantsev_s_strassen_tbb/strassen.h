// Copyright 2020 Rezantsev Sergey
#ifndef MODULES_TASK_3_REZANTSEV_S_STRASSEN_TBB_STRASSEN_H_
#define MODULES_TASK_3_REZANTSEV_S_STRASSEN_TBB_STRASSEN_H_
#include <tbb/task_group.h>
#include <tbb/tbb.h>
#include <vector>
void splitMatrix(std::vector<double> a, std::vector<double> *a11,
                 std::vector<double> *a22, std::vector<double> *a12,
                 std::vector<double> *a21, int n);
std::vector<double> collectMatrix(std::vector<double> a11,
                                  std::vector<double> a22,
                                  std::vector<double> a12,
                                  std::vector<double> a21, int m);
void strassen(const std::vector<double> &a, const std::vector<double> &b,
              std::vector<double> *result);
int checkSize(int n);
std::vector<double> resizeMatrix(std::vector<double> a, int n);
std::vector<double> sumMatrix(std::vector<double> a, std::vector<double> b,
                              int n);
std::vector<double> subtMatrix(std::vector<double> a, std::vector<double> b,
                               int n);
std::vector<double> multMatrix(std::vector<double> a, std::vector<double> b,
                               int n);
bool isEqMatrix(std::vector<double> a, std::vector<double> b, int n);
bool isEqMatrix(std::vector<double> a, double *b, int n);
void strassen_tbb(const std::vector<double> &a, const std::vector<double> &b,
                  std::vector<double> *result);
void multMatrix(const std::vector<double> &a, const std::vector<double> &b,
                std::vector<double> *c, int n);
void sum(const std::vector<double> &a, const std::vector<double> &b,
         std::vector<double> *c);
#endif  // MODULES_TASK_3_REZANTSEV_S_STRASSEN_TBB_STRASSEN_H_
