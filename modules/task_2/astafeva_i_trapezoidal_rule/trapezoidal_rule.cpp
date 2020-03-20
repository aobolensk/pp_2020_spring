// Copyright 2020 Astafeva Irina

#include <omp.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "../../../modules/task_2/astafeva_i_trapezoidal_rule/trapezoidal_rule.h"

double calculateIntegral(double(*function)(std::vector<double>), std::vector <std::pair<double, double>> boundaries,
    std::vector<int> partition) {
    int dimensionality = partition.size();
    int segments = 1;
    std::vector<double> delta(dimensionality);
    for (int i = 0; i < dimensionality; i++) {
        delta[i] = (boundaries[i].second - boundaries[i].first) / partition[i];
        segments *= partition[i];
    }
    double result = 0.0;
    #pragma omp parallel shared(result, dimensionality, segments, delta, boundaries, partition)
    {
        std::vector<double> params(dimensionality);
        int const THREAD_NUMBER = omp_get_thread_num();
        int const NUMBER_THREADS = omp_get_num_threads();
        int start = segments / NUMBER_THREADS * THREAD_NUMBER;
        int n = segments / NUMBER_THREADS;
        if ((segments % NUMBER_THREADS) < THREAD_NUMBER) {
            n++;
            start += THREAD_NUMBER;
        } else {
            start += (segments % NUMBER_THREADS);
        }
        for (int i = 0; i < n; i++) {
            int k = i + start;
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
            #pragma omp atomic
                result += term;
        }
    }
    for (int i = 0; i < dimensionality; i++) {
        result *= delta[i];
    }
    return result;
}
