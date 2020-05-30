// Copyright 2020 Bykovskaya Alina
#ifndef MODULES_TASK_3_BYKOVSKAYA_A_SIMPSON_METHOD_SIMPSON_METHOD_H_
#define MODULES_TASK_3_BYKOVSKAYA_A_SIMPSON_METHOD_SIMPSON_METHOD_H_
#include <vector>
#include <functional>
#include <utility>

double calcIntegral(const std::vector<std::pair<double, double>>& scope,
        std::function<double(const std::vector<double>)> f,
        int accurancy = 100, size_t level = 0,
        std::vector<double> fix_var = {});

#endif  // MODULES_TASK_3_BYKOVSKAYA_A_SIMPSON_METHOD_SIMPSON_METHOD_H_
