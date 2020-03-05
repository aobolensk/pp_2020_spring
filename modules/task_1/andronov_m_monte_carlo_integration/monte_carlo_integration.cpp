// Copyright 2020 Andronov Maxim

#include "../../../modules/task_1/andronov_m_monte_carlo_integration/monte_carlo_integration.h"
#include <vector>
#include <random>
#include <ctime>
#include <utility>

double MonteCarloIntegration(const std::function<double
                        (const std::vector<double>)>& integrand,
                        const std::vector<std::pair<double, double>> intervals,
                                                                const size_t& N) {
    if (N <= 0)
        throw - 1;

    size_t num_dims = intervals.size();
    if (num_dims <= 0)
        throw - 1;

    std::random_device rd;
    std::mt19937 gen;
    gen = std::mt19937(rd());

    std::vector<std::uniform_real_distribution<double>> dist(num_dims);
    for (size_t i = 0; i < num_dims; i++)
        dist[i] = std::uniform_real_distribution<double>
                                (intervals[i].first, intervals[i].second);

    std::vector<double> point(num_dims);
    double sum = 0.0;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < num_dims; j++)
            point[j] = dist[j](gen);
        sum += integrand(point);
    }

    double mes = 1.0;
    for (size_t i = 0; i < num_dims; i++) {
        mes *= intervals[i].second - intervals[i].first;
    }

    double answer = (sum*mes) / N;
    return answer;
}
