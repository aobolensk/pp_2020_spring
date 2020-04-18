// Copyright 2020 Sinitsina Maria
#ifndef MODULES_TASK_2_SINITSINA_M_SIMPSON_SIMPSON_H_
#define MODULES_TASK_2_SINITSINA_M_SIMPSON_SIMPSON_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <omp.h>

double Simpson_Integr_OMP(double(*func)(std::vector<double>), std::vector <double> x, std::vector <double> y,
  int n, size_t dimension, std::vector<double> lim);

#endif  // MODULES_TASK_2_SINITSINA_M_SIMPSON_SIMPSON_H_
