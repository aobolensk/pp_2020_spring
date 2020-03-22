// Copyright 2020 Vikhrev Ivan
#include <tbb/tbb.h>
#include <vector>
#include <string>
#include "./sobel_edge_detection.h"
#ifndef OPENCV
#include "gtest/gtest.h"

TEST(parallel_tbb_edge_detection, can_create_image) {
    imageU a;
    ASSERT_EQ(a.cols, 0);
    ASSERT_EQ(a.rows, 0);
    ASSERT_EQ(a.size, 0);
}

TEST(parallel_tbb_edge_detection, can_create_image_with_two_parameters) {
    imageU a{ 2, 2 };
    std::vector<uint8_t> b{ 0, 0, 0, 0 };
    ASSERT_EQ(a.cols, 2);
    ASSERT_EQ(a.rows, 2);
    ASSERT_EQ(a.size, 4);
    ASSERT_EQ(a.data.size(), static_cast <size_t>(4));
    ASSERT_EQ(a.data, b);
}

TEST(parallel_tbb_edge_detection, can_create_image_with_three_parameters) {
    imageU a{ 1, 1, {1} };
    ASSERT_EQ(a.cols, 1);
    ASSERT_EQ(a.rows, 1);
    ASSERT_EQ(a.size, 1);
    ASSERT_EQ(a.data.size(), static_cast <size_t>(1));
    ASSERT_EQ(a.data[0], 1);
}

TEST(parallel_tbb_edge_detection, is_equal_to_yourself) {
    imageU a{ 1, 1 };
    ASSERT_EQ(a, a);
}

TEST(parallel_tbb_edge_detection, equal_images_are_equal) {
    imageU a{ 1, 1, {1} };
    imageU b{ 1, 1, {1} };
    ASSERT_EQ(a, b);
}

TEST(parallel_tbb_edge_detection, not_equal_images_are_not_equal) {
    imageU a{ 1, 1, {1} };
    imageU b{ 1, 1, {2} };
    ASSERT_NE(a, b);
}

TEST(parallel_tbb_edge_detection, can_copy_image) {
    imageU a{ 1, 1, {1} };
    imageU b{ a };
    ASSERT_EQ(a, b);
}

TEST(parallel_tbb_edge_detection, can_randomize_image) {
    imageU a;
    a.randImage(2, 2);
    ASSERT_EQ(a.cols, 2);
    ASSERT_EQ(a.rows, 2);
    ASSERT_EQ(a.size, 4);
    ASSERT_EQ(a.data.size(), static_cast <size_t>(4));
}

TEST(parallel_tbb_edge_detection, image_change_after_applying_sobel) {
    imageU a{ 3, 3, {1, 1, 1, 1, 1, 1, 1, 1, 1} };
    imageU res =  sobel_par(a);
    ASSERT_NE(a, res);
}

TEST(parallel_tbb_edge_detection, parallel_processed_image_is_equal_to_sequence_processed) {
    imageU a{ 3, 3, {1, 1, 1, 1, 1, 1, 1, 1, 1} };
    imageU res_seq = sobel_seq(a);
    imageU res_par = sobel_par(a);
    ASSERT_EQ(res_seq, res_par);
}

// TEST(parallel_tbb_edge_detection, seq_processed_image_time) {
//     imageU a;
//     a.randImage(10000, 10000);
//     tbb::tick_count t0 = tbb::tick_count::now();
//     imageU res_seq = sobel_seq(a);
//     tbb::tick_count t1 = tbb::tick_count::now();
//     std::cout << (t1 - t0).seconds() << std::endl;
// }

// TEST(parallel_tbb_edge_detection, parallel_processed_image_time) {
//     imageU a;
//     a.randImage(10000, 10000);
//     tbb::tick_count t0 = tbb::tick_count::now();
//     imageU res_par = sobel_par(a);
//     tbb::tick_count t1 = tbb::tick_count::now();
//     std::cout << (t1 - t0).seconds() << std::endl;
// }

#else
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#endif  // opencv

int main(int argc, char **argv) {
#ifndef OPENCV
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    cv::Mat src = cv::imread(static_cast<std::string>(argv[1]), 2);
    cv::imshow("origin", src);
    std::vector<uchar> vec(src.data, src.data + src.cols*src.rows);
    imageU img{ src.rows, src.cols, vec };
    imageU res = sobel_par(img);
    cv::Mat r{ res.rows, res.cols, CV_8UC1, &res.data[0] };
    cv::imshow("res", r);
    cv::waitKey(0);
    return 0;
#endif  // opencv
}
