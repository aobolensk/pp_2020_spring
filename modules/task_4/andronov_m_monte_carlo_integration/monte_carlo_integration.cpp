// Copyright 2020 Andronov Maxim

#include "../../../modules/task_4/andronov_m_monte_carlo_integration/monte_carlo_integration.h"
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <utility>
#include <stdexcept>
#include <iostream>

double SeqMonteCarloIntegration(const std::function<double
                        (const std::vector<double>)>& integrand,
                        const std::vector<std::pair<double, double>> intervals,
                                                                const size_t& N) {
    if (N <= 0)
        throw std::runtime_error("Number of points must be more than 0");

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

const size_t numberOfThread = 2;

void sumOfFunctionValue(const size_t delta, const std::function<double(const std::vector<double>)> integrand,
                       const std::vector<std::pair<double, double>> intervals, double& sum, std::mutex& mutex) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    size_t num_dims = intervals.size();
    std::vector<double> point(num_dims);
    double localSum = 0.0;
    for (size_t i = 0; i < delta; i++) {
        for (size_t j = 0; j < num_dims; j++)
            point[j] = intervals[j].first + (intervals[j].second - intervals[j].first) * dist(gen);
        localSum += integrand(point);
    }

    std::lock_guard<std::mutex> locked(mutex);
    sum += localSum;
}

double ParallelMonteCarloIntegration(const std::function<double(const std::vector
                                            <double>)>& integrand, const std::vector
                                <std::pair<double, double>> intervals, const int& N) {
    if (N <= 0)
        throw std::runtime_error("Number of points must be more than 0");

    const size_t num_dims = intervals.size();
    if (num_dims <= 0)
        throw std::runtime_error("Number of dims must be more than 0");

    std::vector<std::thread> threads;
    std::mutex mutex;
    const size_t delta = N / numberOfThread;
    const size_t rem = N % numberOfThread;
    double sum = 0.0;

    for (size_t i = 0; i < numberOfThread - 1; i++)
        threads.push_back(std::thread(sumOfFunctionValue, delta, integrand, intervals, std::ref(sum), std::ref(mutex)));
    threads.push_back(std::thread(sumOfFunctionValue, delta + rem, integrand, intervals, std::ref(sum), std::ref(mutex)));

    for (auto& t : threads)
        t.join();

    double mes = 1.0;
    for (size_t i = 0; i < num_dims; i++)
        mes *= intervals[i].second - intervals[i].first;

    double answer = (sum * mes) / N;
    return answer;
}

