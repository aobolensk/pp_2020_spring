// Copyright 2020 Rezantsev Sergey
#ifndef MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
#define MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
#include <time.h>
#include <random>
#include <vector>
using namespace std;

void splitMatrix(vector<double> a, vector<double> &a11, vector<double> &a22,
                 vector<double> &a12, vector<double> &a21,
                 int n);
vector<double> collectMatrix(vector<double> a11, vector<double> a22,
                             vector<double> a12, vector<double> a21,
                      int m);
vector<double> strassen(vector<double> a, vector<double> b, int n);
int checkSize(int n);
vector<double> resizeMatrix(vector<double> a, int n);
vector<double> sumMatrix(vector<double> a, vector<double> b, int n);
vector<double> subtMatrix(vector<double> a, vector<double> b, int n);
vector<double> multMatrix(vector<double> a, vector<double> b, int n);
bool isEqMatrix(vector<double> a, vector<double> b, int n);
#endif  // MODULES_TASK_1_REZANTSEV_S_STRASSEN_STRASSEN_H_
