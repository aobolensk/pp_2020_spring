// Copyright 2020 Andronov Maxim

#include "../../../modules/task_2/andronov_m_monte_carlo_integration/monte_carlo_integration.h"
#include <omp.h>
#include <vector>
#include <random>
#include <ctime>
#include <utility>
#include <stdexcept>

double SeqMonteCarloIntegration(const std::function<double
                        (const std::vector<double>)>& integrand,
                        const std::vector<std::pair<double, double>> intervals,
                                                                const size_t& N) {
    if (N <= 0)
        throw std::runtime_error("Number of dots must be more than 0");

    size_t num_dims = intervals.size();
    if (num_dims <= 0)
        throw std::runtime_error("Number of dims must be more than 0");

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::vector<double> point(num_dims);
    double sum = 0.0;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < num_dims; j++)
            point[j] = intervals[j].first + (intervals[j].second - intervals[j].first) * dist(gen);
        sum += integrand(point);
    }

    double mes = 1.0;
    for (size_t i = 0; i < num_dims; i++) {
        mes *= intervals[i].second - intervals[i].first;
    }

    double answer = (sum*mes) / N;
    return answer;
}

double ParallelMonteCarloIntegration(const std::function<double(const std::vector
                                            <double>)>& integrand, const std::vector
                                <std::pair<double, double>> intervals, const int& N) {
    if (N <= 0)
        throw std::runtime_error("Number of dots must be more than 0");

    const int num_dims = intervals.size();
    if (num_dims <= 0)
        throw std::runtime_error("Number of dims must be more than 0");

    std::uniform_real_distribution<double> dist(0.0, 1.0);

    double sum = 0.0;
    #pragma omp parallel reduction(+: sum)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::vector<double> point(num_dims);

        #pragma omp for
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < num_dims; j++)
                point[j] = intervals[j].first + (intervals[j].second - intervals[j].first) * dist(gen);
            sum += integrand(point);
        }
    }

    double mes = 1.0;
    for (int i = 0; i < num_dims; i++) {
        mes *= intervals[i].second - intervals[i].first;
    }

    double answer = (sum * mes) / N;
    return answer;
}

