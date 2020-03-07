// Copyright 2020 Denisov Vladislav
#include <gtest/gtest.h>
#include <functional>
#include <vector>
#include "./monte_karlo.h"

#define NUMBER_POINTS 100000

TEST(monte_carlo_seq, throw_when_number_points_zero) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt = { 0 };
    std::vector<double> highLimInt = { 2 };

    EXPECT_ANY_THROW(getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, 0, 10));
}

TEST(monte_carlo_seq, throw_when_integ_lim_is_empty) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt;
    std::vector<double> highLimInt = { 1 };

    EXPECT_ANY_THROW(getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, NUMBER_POINTS, 10));
}

TEST(monte_carlo_seq, throw_when_dim_for_integ_lim_non_equal) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt = { 0, 1 };
    std::vector<double> highLimInt = { 2 };

    EXPECT_ANY_THROW(getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, NUMBER_POINTS, 10));
}

TEST(monte_carlo_seq, integral_const) {
    // f = 10
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return 10; };

    std::vector<double> lowLimInt = { 0 };
    std::vector<double> highLimInt = { 1 };

    double result = getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(result, 10.0, 0.05);
}

TEST(monte_carlo_seq, integral_one_dim_func_linear) {
    // f = x
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0]); };

    std::vector<double> lowLimInt = { 0 };
    std::vector<double> highLimInt = { 2 };

    double result = getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(result, 2.0, 0.05);
}

TEST(monte_carlo_seq, integral_two_dim_func) {
    // f = x1 * x2 / 4
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0] * x[1] / 4.0); };

    std::vector<double> lowLimInt = { 2, 1 };
    std::vector<double> highLimInt = { 3, 4 };

    double result = getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(result, 4.6875, 0.05);
}

TEST(monte_carlo_seq, integral_third_dim_func) {
    // f = x1 * x1 + x2 * x2 + x3 * x3
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return (x[0] * x[0] + x[1] * x[1] + x[2] * x[2]); };

    std::vector<double> lowLimInt = { 1, 1, 1 };
    std::vector<double> highLimInt = { 1.5, 1.5, 1.5 };

    double result = getIntegralMonteCarloSeq(func, lowLimInt, highLimInt, NUMBER_POINTS, 10);

    EXPECT_NEAR(result, 0.59375, 0.05);
}
