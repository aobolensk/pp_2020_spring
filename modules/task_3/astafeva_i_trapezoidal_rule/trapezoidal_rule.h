// Copyright 2020 Astafeva Irina
#ifndef MODULES_TASK_3_ASTAFEVA_I_TRAPEZOIDAL_RULE_TRAPEZOIDAL_RULE_H_
#define MODULES_TASK_3_ASTAFEVA_I_TRAPEZOIDAL_RULE_TRAPEZOIDAL_RULE_H_

#include <vector>
#include <utility>

double calculateIntegral(double(*function)(std::vector<double>), std::vector <std::pair<double, double>> boundaries,
    std::vector<int> partition);

#endif  // MODULES_TASK_3_ASTAFEVA_I_TRAPEZOIDAL_RULE_TRAPEZOIDAL_RULE_H_
