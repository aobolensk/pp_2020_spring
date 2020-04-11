// Copyright 2020 Andronov Maxim

#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <functional>
#include <cmath>
#include "./monte_carlo_integration.h"

const size_t N = 10000;

TEST(MonteCarloIntegration, omp_one_dims_sin) {
    const size_t dims = 1;
    std::function<double(const std::vector<double>&)> integrand =
        [](const std::vector<double>& points) { return sin(points[0]); };
    const double pi = 3.141592;
    std::vector <std::pair<double, double>> intervals(dims);
    intervals[0] = { 0.0, pi / 2 };

    double answer = ParallelMonteCarloIntegration(integrand, intervals, N);
    double real_answer = 1.0;

    ASSERT_NEAR(real_answer, answer, 0.5);
}

TEST(MonteCarloIntegration, omp_one_dims_quadratic) {
    const size_t dims = 1;
    std::function<double(const std::vector<double>&)> integrand =
        [](const std::vector<double>& points) { return points[0] * points[0]; };
    std::vector <std::pair<double, double>> intervals(dims);
    intervals[0] = { 0.0, 5.0 };

    double answer = ParallelMonteCarloIntegration(integrand, intervals, N);
    double real_answer = 41.6667;

    ASSERT_NEAR(real_answer, answer, 2.0);
}

TEST(MonteCarloIntegration, omp_two_dims_hyperboloid) {
    const size_t dims = 2;
    std::function<double(const std::vector<double>&)> integrand =
        [](const std::vector<double>& points) { return pow(points[0], 2) + pow(points[1], 2); };
    std::vector <std::pair<double, double>> intervals(dims);
    intervals[0] = { -2.0, 2.0 };
    intervals[1] = { -2.0, 2.0 };

    double answer = ParallelMonteCarloIntegration(integrand, intervals, N);
    double real_answer = 42.6667;

    ASSERT_NEAR(real_answer, answer, 2.0);
}

TEST(MonteCarloIntegration, omp_two_dims_inverse_hyperboloid) {
    const size_t dims = 2;
    std::function<double(const std::vector<double>&)> integrand =
        [](const std::vector<double>& points) { return -pow(points[0], 2) - pow(points[1], 2) + 3; };
    std::vector <std::pair<double, double>> intervals(dims);
    intervals[0] = { -2.0, 2.0 };
    intervals[1] = { -2.0, 2.0 };

    double answer = ParallelMonteCarloIntegration(integrand, intervals, N);
    double real_answer = 5.3334;

    ASSERT_NEAR(real_answer, answer, 2.0);
}

TEST(MonteCarloIntegration, omp_three_dims_integral) {
    const size_t dims = 3;
    std::function<double(const std::vector<double>&)> integrand =
        [](const std::vector<double>& points)
    { return pow(points[0], 2) * points[2] * sin(points[0] * points[1] * points[2]); };
    const double pi = 3.141592;
    std::vector <std::pair<double, double>> intervals(dims);
    intervals[0] = { 0.0, 2.0 };
    intervals[1] = { 0.0, pi };
    intervals[2] = { 0.0, 1.0 };

    double answer = ParallelMonteCarloIntegration(integrand, intervals, N);
    double real_answer = 2.0;

    ASSERT_NEAR(real_answer, answer, 1.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

