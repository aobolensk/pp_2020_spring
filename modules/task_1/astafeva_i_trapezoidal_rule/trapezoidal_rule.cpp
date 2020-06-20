// Copyright 2020 Astafeva Irina

#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "../../../modules/task_1/astafeva_i_trapezoidal_rule/trapezoidal_rule.h"

double calculateIntegral(double (*function)(std::vector<double>), std::vector <std::pair<double, double>> boundaries,
                        std::vector<int> partition) {
    int dimensionality = partition.size();
    int segments = 1;
    std::vector<double> delta(dimensionality);
    for (int i = 0; i < dimensionality; i++) {
        delta[i] = (boundaries[i].second - boundaries[i].first) / partition[i];
        segments *= partition[i];
    }
    double result = 0.0;
    std::vector<double> params(dimensionality);
    for (int i = 0; i < segments; i++) {
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
    for (int i = 0; i < dimensionality; i++) {
        result *= delta[i];
    }
    return result;
}
