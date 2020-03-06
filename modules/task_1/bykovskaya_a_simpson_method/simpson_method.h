// Copyright 2020 Bykovskaya Alina
#ifndef MODULES_TASK_1_BYKOVSKAYA_A_SIMPSON_METHOD_SIMPSON_METHOD_H_
#define MODULES_TASK_1_BYKOVSKAYA_A_SIMPSON_METHOD_SIMPSON_METHOD_H_
#include <vector>
#include <functional>

double calcIntegral(const std::vector<std::pair<double, double>>& scope,
        std::function<double(const std::vector<double>)> f,
        int accurancy = 200, int level = 0,
        std::vector<double> fix_var = {});

#endif
