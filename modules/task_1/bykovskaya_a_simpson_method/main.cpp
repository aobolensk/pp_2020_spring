// Copyright 2020 Bykovskaya Alina
#include <gtest/gtest.h>
#include <omp.h>
#include <cmath>
#include <vector>
#include <functional>
#include <utility>
#include "./simpson_method.h"

TEST(Simson_Method_Seq, Can_Integrate_One_Dim_Func) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0]; };  // y(x) = x
    std::vector<std::pair<double, double>> scope = { {0, 1} };  // expected 0.5
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 0.5, 1);
}

TEST(Simson_Method_Seq, Can_Integrate_One_Dim_Func_2) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0] * vec[0] * vec[0]; };  // y(x) = x * x * x
    std::vector<std::pair<double, double>> scope = { {0, 1} };  // expected 0.25
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 0.25, 1);
}

TEST(Simson_Method_Seq, Can_Integrate_Two_Dim_Func) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0] + 2 * sin(vec[1]); };  // y(x) = x + 2 * sin(y)
    std::vector<std::pair<double, double>> scope = { {0, 0.2}, {0, 3.14159} };  // expected 0.862832
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 0.862832, 1);
}

TEST(Simson_Method_Seq, Can_Integrate_Two_Dim_Func_2) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0] + vec[1] * vec[1]; };  // y(x) = x + y*y
    std::vector<std::pair<double, double>> scope = { {0, 1}, {0, 2} };  // expected 3.6
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 3.6, 1);
}

TEST(Simson_Method_Seq, Can_Integrate_Two_Dim_Func_3) {
    std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
        return vec[0] + vec[1]; };  // y(x) = x + y
    std::vector<std::pair<double, double>> scope = { {0, 0.5}, {0, 0.5} };  // expected 0.125
    double res = calcIntegral(scope, f);
    EXPECT_NEAR(res, 0.125, 1);
}

// TEST(Simson_Method_Seq, Can_Integrate_Three_Dim_Func) {
//     std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec){
//         return sin(vec[0]) * vec[1] * cos(vec[2]);};  // f(x,y,z) = sin(x) * y * cos(z)
//     std::vector<std::pair<double, double>> scope = { {0, 1}, {-2, 2}, {3, 7} };  // expected 0
//     double res = calcIntegral(scope, f);
//     EXPECT_NEAR(res, 0.0, 1);
// }

// TEST(Simson_Method_Seq, Can_Integrate_Three_Dim_Func_2) {
//     std::function<double(const std::vector<double>&)> f = [](const std::vector<double>& vec) {
//         return vec[0] + vec[1] + vec[2];};  // f(x,y,z) = x + y + z
//     std::vector<std::pair<double, double>> scope = { {0, 1}, {0, 0.5}, {0, 0.5} };  // expected 0.25
//     double res = calcIntegral(scope, f);
//     EXPECT_NEAR(res, 0.25, 1);
// }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
