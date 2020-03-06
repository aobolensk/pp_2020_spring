// Copyright 2020 Yakovlev Pavel
#include <vector>
#include <iostream>
#include <utility>
#include "./Jarvis_algorithm.h"
#ifndef OPENCV
#include <gtest/gtest.h>


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
#else
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#endif  // opencv

int main(int argc, char **argv) {
#ifndef OPENCV
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    cv::Mat src = cv::Mat::zeros(600, 600, CV_8UC3);
    auto points = getRandomVectorOfPair(10);
    for (auto p : points)
        std::cout << p.first << " " << p.second << std::endl;
    for (auto p : points) {
        uint x = static_cast<uint>(p.first);
        uint y = 600 - static_cast<uint>(p.second);
        circle(src, cv::Point(x, y), 5, cv::Scalar(255, 255, 255), CV_FILLED, 8, 0);
    }
    auto  res = ConvexHull_Jarvis(points);
    for (auto p : res) {
        uint x = static_cast<uint>(p.first);
        uint y = 600 - static_cast<uint>(p.second);
        circle(src, cv::Point(x, y), 5, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
    }
    cv::imshow("Image", src);
    cv::waitKey(0);
    return 0;
#endif  // opencv
}
