// Copyright 2020 Denisov Vladislav
#include <gtest/gtest.h>
#include <iostream>
#include <functional>
#include <vector>
#include <ctime>
#include "./monte_karlo.h"

#define NUMBER_POINTS 100000

TEST(monte_carlo_par, throw_when_number_points_zero) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt = { 0 };
    std::vector<double> highLimInt = { 2 };

    EXPECT_ANY_THROW(getIntegralMonteCarloPar(func, lowLimInt, highLimInt, 0, 10));
}

TEST(monte_carlo_par, throw_when_integ_lim_is_empty) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt;
    std::vector<double> highLimInt = { 1 };

    EXPECT_ANY_THROW(getIntegralMonteCarloPar(func, lowLimInt, highLimInt, NUMBER_POINTS, 10));
}

TEST(monte_carlo_par, throw_when_dim_for_integ_lim_non_equal) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt = { 0, 1 };
    std::vector<double> highLimInt = { 2 };

    EXPECT_ANY_THROW(getIntegralMonteCarloPar(func, lowLimInt, highLimInt, NUMBER_POINTS, 10));
}

TEST(monte_carlo_par, integral_const) {
    // f = 10
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return 10; };

    std::vector<double> lowLimInt = { 0 };
    std::vector<double> highLimInt = { 1 };

    double result = getIntegralMonteCarloPar(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(result, 10.0, 0.05);
}

TEST(monte_carlo_par, integral_one_dim_func_linear) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt = { 0 };
    std::vector<double> highLimInt = { 2 };

    double result = getIntegralMonteCarloPar(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(result, 2.0, 0.05);
}

TEST(monte_carlo_par, integral_two_dim_func) {
    // f = x1 * x2 / 4
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0] * x[1] / 4.0); };

    std::vector<double> lowLimInt = { 2, 1 };
    std::vector<double> highLimInt = { 3, 4 };

    double result = getIntegralMonteCarloPar(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(result, 4.6875, 0.05);
}

TEST(monte_carlo_par, integral_third_dim_func) {
    // f = x1 * x1 + x2 * x2 + x3 * x3
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0] * x[0] + x[1] * x[1] + x[2] * x[2]); };

    std::vector<double> lowLimInt = { 1, 1, 1 };
    std::vector<double> highLimInt = { 1.5, 1.5, 1.5 };

    double result = getIntegralMonteCarloPar(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(result, 0.59375, 0.05);
}

TEST(monte_carlo_par, integral_par_and_seq_equal_check) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt = { 0 };
    std::vector<double> highLimInt = { 2 };

    double resultpar = getIntegralMonteCarloPar(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);
    double resultseq = getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(resultpar, resultseq, 0.05);
}

TEST(monte_carlo_par, DISABLED_integral_time_check) {
    // f = x1 * x1 * x1 + x2 * x2 * x2 + x3 * x3 * x3
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0] * x[0] * x[0] + x[1] * x[1] * x[1] + x[2] * x[2] * x[2]); };

    std::vector<double> lowLimInt = { 0, 0, 0 };
    std::vector<double> highLimInt = { 1.5, 1.5, 1.5 };

    std::clock_t t1 = clock();
    double resultseq = getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, 100 * NUMBER_POINTS, 10);
    std::clock_t t2 = clock();
    double seqTime = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "SEQUENTAL: " << seqTime << std::endl;

    t1 = clock();
    double resultpar = getIntegralMonteCarloPar(func, lowLimInt, highLimInt, 100 * NUMBER_POINTS, 10);
    t2 = clock();
    double parTime = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    std::cout << "STD THREADS: " << parTime << std::endl;

    EXPECT_NEAR(resultpar, resultseq, 0.05);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
