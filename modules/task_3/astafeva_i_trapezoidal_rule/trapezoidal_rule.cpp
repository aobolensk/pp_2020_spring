// Copyright 2020 Astafeva Irina

#include <cmath>
#include <functional>
#include <iostream>
#include <vector>
#include <utility>
#include "tbb/tbb.h"
#include "../../../modules/task_3/astafeva_i_trapezoidal_rule/trapezoidal_rule.h"

double calculateIntegral(double(*function)(std::vector<double>), std::vector <std::pair<double, double>> boundaries,
    std::vector<int> partition) {
    int dimensionality = partition.size();
    int segments = 1;
    std::vector<double> delta(dimensionality);
    for (int i = 0; i < dimensionality; i++) {
        delta[i] = (boundaries[i].second - boundaries[i].first) / partition[i];
        segments *= partition[i];
    }
    double res = tbb::parallel_reduce(tbb::blocked_range<int>(0, segments), 0.0,
        [&](tbb::blocked_range<int> r, double result) {
            for (int i = r.begin(); i != r.end(); i++) {
                std::vector<double> params(dimensionality);
                int k = i;
                for (int j = 0; j < dimensionality; j++) {
                    params[j] = boundaries[j].first + delta[j] * (k % partition[j]);
                    k /= partition[j];
                }
                double term = function(params);
                for (int j = 0; j < dimensionality; j++) {
                    if (params[j] == boundaries[j].first) {
                        term /= 2;
                    }
                    if (params[j] == boundaries[j].second) {
                        term /= 2;
                    }
                }
                result += term;
            }
            return result;
        }, std::plus<double>());

    for (int i = 0; i < dimensionality; i++) {
        res *= delta[i];
    }
    return res;
}
