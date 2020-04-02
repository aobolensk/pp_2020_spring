// Copyright 2020 Sinitsina Maria
#ifndef MODULES_TASK_1_SINITSINA_M_SIMPSON_SIMPSON_H_
#define MODULES_TASK_1_SINITSINA_M_SIMPSON_SIMPSON_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

double SequentialIntegr(double(*func)(std::vector<double>), std::vector <double> x,
  std::vector <double> y, const int n);

#endif  // MODULES_TASK_1_SINITSINA_M_SIMPSON_SIMPSON_H_
