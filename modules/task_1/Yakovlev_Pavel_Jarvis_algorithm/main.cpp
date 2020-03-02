// Copyright 2020 Yakovlev Pavel
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <utility>
#include "./Jarvis_algorithm.h"

TEST(Sequential_algorithm, Test_default_hull) {
    std::vector<std::pair<double, double>> points {
        std::make_pair(4.0, 2.0),
        std::make_pair(3.0, 3.0),
        std::make_pair(2.0, 4.0),
        std::make_pair(1.0, 1.0),
        std::make_pair(5.0, 4.0)
    };
    std::vector<std::pair<double, double>> trueResult {
        std::make_pair(1.0, 1.0),
        std::make_pair(4.0, 2.0),
        std::make_pair(5.0, 4.0),
        std::make_pair(2.0, 4.0)
    };
    auto  res = ConvexHull_Jarvis(points);
    ASSERT_EQ(res, trueResult);
}

TEST(Sequential_algorithm, Test_two_points) {
    std::vector<std::pair<double, double>> points {
        std::make_pair(4.0, 8.0),
        std::make_pair(4.0, 2.0)
    };
    std::vector<std::pair<double, double>> trueResult {
        std::make_pair(4.0, 2.0),
        std::make_pair(4.0, 8.0)
    };
    auto  res = ConvexHull_Jarvis(points);
    ASSERT_EQ(res, trueResult);
}

TEST(Sequential_algorithm, Test_two_eq_points) {
    std::vector<std::pair<double, double>> points {
        std::make_pair(4.0, 8.0),
        std::make_pair(4.0, 8.0)
    };
    std::vector<std::pair<double, double>> trueResult {
        std::make_pair(4.0, 8.0)
    };
    auto  res = ConvexHull_Jarvis(points);
    ASSERT_EQ(res, trueResult);
}

TEST(Sequential_algorithm, Test_one_point) {
    std::vector<std::pair<double, double>> points {
        std::make_pair(4.0, 8.0)
    };
    std::vector<std::pair<double, double>> trueResult {
        std::make_pair(4.0, 8.0)
    };
    auto  res = ConvexHull_Jarvis(points);
    ASSERT_EQ(res, trueResult);
}

TEST(Sequential_algorithm, Test_some_eq_points) {
    std::vector<std::pair<double, double>> points {
        std::make_pair(4.0, 2.0),
        std::make_pair(4.0, 2.0),
        std::make_pair(3.0, 3.0),
        std::make_pair(3.0, 3.0),
        std::make_pair(2.0, 4.0),
        std::make_pair(2.0, 4.0),
        std::make_pair(1.0, 1.0),
        std::make_pair(1.0, 1.0),
        std::make_pair(5.0, 4.0),
        std::make_pair(5.0, 4.0),
        std::make_pair(3.0, 3.0)
    };
    std::vector<std::pair<double, double>> trueResult {
        std::make_pair(1.0, 1.0),
        std::make_pair(4.0, 2.0),
        std::make_pair(5.0, 4.0),
        std::make_pair(2.0, 4.0)
    };
    auto  res = ConvexHull_Jarvis(points);
    ASSERT_EQ(res, trueResult);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
