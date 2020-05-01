// Copyright 2020 lesya89
#include <vector>
#include <string>
#include "./gauss_filter.h"
#ifndef OPENCV
#include "gtest/gtest.h"

TEST(sequential_gauss_filter, can_create_random_image) {
    ASSERT_NO_THROW(Image test = Image(10, 10, true));
}

TEST(sequential_gauss_filter, image_copying_is_correct) {
    Image test = Image(10, 10, true);
    Image test2(test);
    EXPECT_EQ((test == test2), true);
}

TEST(sequential_gauss_filter, image_changes_after_filtering) {
    Image test = Image(10, 10, true);
    EXPECT_NE(test, test.GaussFilter());
}

TEST(sequential_gauss_filter, can_filter_large_image) {
    Image test = Image(50, 50, true);
    ASSERT_NO_THROW(test.GaussFilter());
}

TEST(sequential_gauss_filter, filtering_is_correct) {
    unsigned char src[9] = { 16, 16, 16, 16, 32, 16, 16, 16, 16 };
    unsigned char dst[9] = { 0, 0, 0, 0, 20, 0, 0, 0, 0 };
    Image in = Image(3, 3, src);
    Image out = Image(3, 3, dst);
    EXPECT_EQ((in.GaussFilter() == out), true);
}

#else
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#endif

int main(int argc, char **argv) {
#ifndef OPENCV
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    cv::Mat src = cv::imread("C:\\test.jpg", 2);
    cv::imshow("Source image", src);

    Image test = Image(src.rows, src.cols, src.data);
    Image res = test.GaussFilter();
    cv::Mat dst = cv::Mat(res.rows, res.cols, CV_8UC1, res.data);

    cv::imshow("Result image", dst);
    cv::waitKey(0);
    return 0;
#endif
}
