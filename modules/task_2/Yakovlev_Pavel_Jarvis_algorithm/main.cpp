// Copyright 2020 Yakovlev Pavel
#include <omp.h>
#include <vector>
#include <iostream>
#include <utility>
#include "./Jarvis_algorithm.h"
#ifndef OPENCV
#include <gtest/gtest.h>


TEST(OMP_algorithm, Test_default_hull) {
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
    auto  res = ConvexHull_Jarvis_omp(points);
    ASSERT_EQ(res, trueResult);
}

TEST(OMP_algorithm, Test_two_points) {
    std::vector<std::pair<double, double>> points {
        std::make_pair(4.0, 8.0),
        std::make_pair(4.0, 2.0)
    };
    std::vector<std::pair<double, double>> trueResult {
        std::make_pair(4.0, 2.0),
        std::make_pair(4.0, 8.0)
    };
    auto  res = ConvexHull_Jarvis_omp(points);
    ASSERT_EQ(res, trueResult);
}

TEST(OMP_algorithm, Test_two_eq_points) {
    std::vector<std::pair<double, double>> points {
        std::make_pair(4.0, 8.0),
        std::make_pair(4.0, 8.0)
    };
    std::vector<std::pair<double, double>> trueResult {
        std::make_pair(4.0, 8.0)
    };
    auto  res = ConvexHull_Jarvis_omp(points);
    ASSERT_EQ(res, trueResult);
}

TEST(OMP_algorithm, Test_one_point) {
    std::vector<std::pair<double, double>> points {
        std::make_pair(4.0, 8.0)
    };
    std::vector<std::pair<double, double>> trueResult {
        std::make_pair(4.0, 8.0)
    };
    auto  res = ConvexHull_Jarvis_omp(points);
    ASSERT_EQ(res, trueResult);
}

TEST(OMP_algorithm, Test_some_eq_points) {
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
    auto  res = ConvexHull_Jarvis_omp(points);
    ASSERT_EQ(res, trueResult);
}

TEST(OMP_algorithm, Test_time_algo) {
    auto points = getRandomVectorOfPair(10);

    double start1 = omp_get_wtime();
    auto  seq = ConvexHull_Jarvis_seq(points);
    double end1 = omp_get_wtime();
    std::cout<< "Time seq: " << end1 - start1 << std::endl;
    double start2 = omp_get_wtime();
    auto  omp = ConvexHull_Jarvis_omp(points);
    double end2 = omp_get_wtime();
    std::cout << "Time omp: " << end2 - start2 << std::endl;
    std::cout << "scalability: " << (end1 - start1)/(end2 - start2) << std::endl;

    ASSERT_EQ(omp, seq);
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
    auto  res = ConvexHull_Jarvis_omp(points);
    for (auto p : res) {
        uint x = static_cast<uint>(p.first);
        uint y = 600 - static_cast<uint>(p.second);
        circle(src, cv::Point(x, y), 5, cv::Scalar(0, 255, 0), CV_FILLED, 8, 0);
    }

    for (size_t i = 0; i < res.size() - 1; i++) {
        uint x1 = static_cast<uint>(res[i].first);
        uint y1 = 600 - static_cast<uint>(res[i].second);
        uint x2 = static_cast<uint>(res[i+1].first);
        uint y2 = 600 - static_cast<uint>(res[i+1].second);
        cv::line(src, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255), 4);
    }

    uint x1 = static_cast<uint>(res[0].first);
    uint y1 = 600 - static_cast<uint>(res[0].second);
    uint x2 = static_cast<uint>(res[res.size()-1].first);
    uint y2 = 600 - static_cast<uint>(res[res.size() - 1].second);
    cv::line(src, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255), 4);

    cv::imshow("Image", src);
    cv::waitKey(0);
    return 0;
#endif  // opencv
}
