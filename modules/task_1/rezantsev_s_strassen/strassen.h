// Copyright 2020 Rezantsev Sergey
#ifndef MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
#define MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
#include <time.h>
#include <random>
void splitMatrix(double* a, double* a11, double* a22, double* a12, double* a21,
                 int n);
double* collectMatrix(double* a11, double* a22, double* a12, double* a21,
                      int m);
double* strassen(double* a, double* b, int n);
int checkSize(int n);
double* resizeMatrix(double* a, int n);
double* sumMatrix(double* a, double* b, int n);
double* subtMatrix(double* a, double* b, int n);
double* multMatrix(double* a, double* b, int n);
bool isEqMatrix(double* a, double* b, int n);
#endif  // MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
