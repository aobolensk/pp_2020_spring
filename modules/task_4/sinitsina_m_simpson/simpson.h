// Copyright 2020 Sinitsina Maria
#ifndef MODULES_TASK_4_SINITSINA_M_SIMPSON_SIMPSON_H_
#define MODULES_TASK_4_SINITSINA_M_SIMPSON_SIMPSON_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <mutex>

double Simpson_Integr_std(double(*func)(std::vector<double>), std::vector <double> x, std::vector <double> y,
  int n, size_t dimension, std::vector<double> lim);

double Simpson_Integr_seq(double(*func)(std::vector<double>), std::vector <double> x,
  std::vector <double> y, int n, size_t dimension, std::vector<double> lim);

void calc_func_res(double(*func)(std::vector<double>), std::vector <double> x, size_t dimension, double h, std::vector<double>& func_res, int N, int start, int step);

#endif  // MODULES_TASK_4_SINITSINA_M_SIMPSON_SIMPSON_H_
