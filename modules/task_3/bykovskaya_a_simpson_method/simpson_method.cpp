// Copyright 2020 Bykovskaya Alina
#include "../../../modules/task_3/bykovskaya_a_simpson_method/simpson_method.h"
#include <vector>
#include <functional>
#include <utility>
#include "tbb/tbb.h"

double calcIntegral(const std::vector<std::pair<double, double>>& scope,
        std::function<double(const std::vector<double>)> f, int accurancy,
        size_t level, std::vector<double> fix_var) {
    if (scope.size() == 0)
        throw "Bad scope";
    if (fix_var.size() == 0)
        for (auto i : scope)
            fix_var.push_back(i.first);
    if (level >= scope.size())
        throw "Bad level of recursion";
    double h = (scope[level].second - scope[level].first) / (2 * accurancy);
    std::vector<double> func_res(2 * accurancy);
    if (scope.size() == level + 1) {
        tbb::parallel_for(tbb::blocked_range<int>{0, accurancy * 2, 100},
                [&](const tbb::blocked_range<int>& r) {
                    for (int i = r.begin(); i != r.end(); ++i) {
                        fix_var[level] = scope[level].first + i * h;
                        func_res[i] = f(fix_var);
                    }
                });
    } else {
         tbb::parallel_for(tbb::blocked_range<int>{0, accurancy * 2, 100},
                [&](const tbb::blocked_range<int>& r) {
                    for (int i = r.begin(); i != r.end(); ++i) {
                        fix_var[level] = scope[level].first + i * h;
                        func_res[i] = calcIntegral(scope, f,
                                    accurancy, level + 1, fix_var);
                    }
                });
    }
    double res = func_res[0] + func_res[2 * accurancy - 1];
    if (level == 0) {
        res += tbb::parallel_reduce(tbb::blocked_range<int>{1, 2 * accurancy - 1},
                    0.f,
                    [&](const tbb::blocked_range<int>& r, double part) -> double {
                        for (int i = r.begin(); i != r.end(); ++i)
                            if (i % 2 == 1) {
                                part += 4 * func_res[i];
                            } else {
                                part += 2 * func_res[i];
                            }
                        return part;
                    },
                    std::plus<double>() );
    } else {
        for (int i = 1; i < 2 * accurancy - 1; i += 2)
            res += 4 * func_res[i];
        for (int i = 2; i < 2 * accurancy - 2; i += 2)
            res += 2 * func_res[i];
    }
    // for (size_t i = 1; i < 2 * accurancy - 1; i += 2)
    //     res += 4 * func_res[i];
    // for (size_t i = 2; i < 2 * accurancy - 2; i += 2)
    //     res += 2 * func_res[i];
    res = res * h / 3.0;
    return res;
}
