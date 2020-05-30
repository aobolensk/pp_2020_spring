// Copyright 2020 Astafeva Irina

#include <gtest/gtest.h>
#include <omp.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "../../../modules/task_1/astafeva_i_trapezoidal_rule/trapezoidal_rule.h"

double function1(std::vector<double> params) {
    double x = params[0];
    double y = params[1];
    return (x * x - 2 * y);
}

double function2(std::vector<double> params) {
    double x = params[0];
    double y = params[1];
    return (sqrt(3 * x) + 7 * y);
}

double function3(std::vector<double> params) {
    double x = params[0];
    double y = params[1];
    double z = params[2];
    return (x + y * y + z * z * z);
}

double function4(std::vector<double> params) {
    double x = params[0];
    double y = params[1];
    double z = params[2];
    return (log10(2 * x * x) + sqrt(z) + 5 * y);
}

double function5(std::vector<double> params) {
    double x = params[0];
    double y = params[1];
    double z = params[2];
    return (exp(x) - sqrt(10) * 5 * sin(y) + cos(-2 * z * z));
}

TEST(Trapezoidal_Rule_Seq, function_Of_Two_Variables) {
    int n = 2;
    std::vector<std::pair<double, double>> boundaries(n);
    std::vector<int> partition(n);
    boundaries[0] = { 4, 10 }; partition[0] = 10;
    boundaries[1] = { 1, 56 }; partition[1] = 10;

    double result = calculateIntegral(function1, boundaries, partition);

    ASSERT_NEAR(result, -1650, 300);
}

TEST(Trapezoidal_Rule_Seq, function_Of_Two_Variables_With_Sqrt) {
    int n = 2;
    std::vector<std::pair<double, double>> boundaries(n);
    std::vector<int> partition(n);
    boundaries[0] = { 4, 10 }; partition[0] = 10;
    boundaries[1] = { 1, 56 }; partition[1] = 10;

    double result = calculateIntegral(function2, boundaries, partition);

    ASSERT_NEAR(result, 67335.2, 11000);
}

TEST(Trapezoidal_Rule_Seq, function_Of_Three_Two_Variables) {
    int n = 3;
    std::vector<std::pair<double, double>> boundaries(n);
    std::vector<int> partition(n);
    boundaries[0] = { 0, 1 }; partition[0] = 10;
    boundaries[1] = { -13, 5 }; partition[1] = 10;
    boundaries[2] = { 3, 7 }; partition[2] = 10;

    double result = calculateIntegral(function3, boundaries, partition);

    ASSERT_NEAR(result, 13572, 2500);
}

TEST(Trapezoidal_Rule_Seq, function_Of_Three_Two_Variables_With_Log10_And_Sqrt) {
    int n = 3;
    std::vector<std::pair<double, double>> boundaries(n);
    std::vector<int> partition(n);
    boundaries[0] = { 1, 2 }; partition[0] = 10;
    boundaries[1] = { -13, 5 }; partition[1] = 10;
    boundaries[2] = { 3, 7 }; partition[2] = 10;

    double result = calculateIntegral(function4, boundaries, partition);

    ASSERT_NEAR(result, -1234.28, 28);
}

TEST(Trapezoidal_Rule_Seq, function_Of_Three_Two_Variables_With_Exp_Cos_And_Sin) {
    int n = 3;
    std::vector<std::pair<double, double>> boundaries(n);
    std::vector<int> partition(n);
    boundaries[0] = { -9, 1 }; partition[0] = 10;
    boundaries[1] = { -100, 100 }; partition[1] = 10;
    boundaries[2] = { 2, 2 }; partition[2] = 10;

    double result = calculateIntegral(function5, boundaries, partition);

    ASSERT_NEAR(result, 0, 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
