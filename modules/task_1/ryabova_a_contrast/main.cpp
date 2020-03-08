// Copyright 2020 Ryabova Alyona

#include "./contrast_enhancement.h"

#ifndef OPENCV
#include <gtest/gtest.h>

TEST(contrast_enhancement, correct_calculate_by_formula) {
    int width = 2;
    int height = 2;

    Image img{ 54, 100, 78, 130 };
    Image res{ 0, 154, 80, 255 };

    ASSERT_EQ(res, contrastImage(img, width, height));
}

TEST(contrast_enhancement, get_black_img_when_pix_are_the_same) {
    int width = 2;
    int height = 2;

    Image img{ 100, 100, 100, 100 };
    Image res{ 0, 0, 0, 0 };

    ASSERT_EQ(res, contrastImage(img, width, height));
}

TEST(contrast_enhancement, can_change_small_img) {
    int width = 10;
    int height = 10;

    Image img = randomImage(width, height);

    ASSERT_NE(img, contrastImage(img, width, height));
}

TEST(contrast_enhancement, can_change_big_img) {
    int width = 945;
    int height = 345;

    Image img = randomImage(width, height);

    ASSERT_NE(img, contrastImage(img, width, height));
}

TEST(contrast_enhancement, any_throw_when_error_size) {
    int width1 = 100;
    int width2 = 100;
    int height = 100;

    Image img = randomImage(width1, height);

    ASSERT_ANY_THROW(img, contrastImage(img, width2, height));
}

#else
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <string>
#include <vector>

void show_histogram(std::string const& name, cv::Mat1b const& image) {
    // histogram bins count
    int bins = 256;
    int histSize[] = { bins };
    // ranges for histogram bins
    float lranges[] = { 0, 256 };
    const float* ranges[] = { lranges };
    // matrix for histogram
    cv::Mat hist;
    int channels[] = { 0 };

    // create matrix for histogram visualization
    int const hist_height = 256;
    cv::Mat3b hist_image = cv::Mat3b::zeros(hist_height, bins);

    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

    double max_val = 0;
    minMaxLoc(hist, 0, &max_val);

    // visualize each bin
    for (int b = 0; b < bins; b++) {
        float const binVal = hist.at<float>(b);
        int   const height = cvRound(binVal * hist_height / max_val);
        cv::line
        (hist_image
            , cv::Point(b, hist_height - height), cv::Point(b, hist_height)
            , cv::Scalar::all(255));
    }
    cv::imshow(name, hist_image);
}

#endif

int main(int argc, char** argv) {
    #ifndef OPENCV
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    #else
    cv::Mat src = cv::imread("C:/Users/User/Pictures/4.png");
    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    std::vector <int> vec(src.rows * src.cols);
    cv::imshow("first", src);
    cv::waitKey(0);

    show_histogram("image1 hist", src);
    cv::waitKey(0);

    int n = 0;
    for (int j = 0; j < src.rows; j++) {
        for (int i = 0; i < src.cols; i++) {
            vec[n++] = static_cast<int>(src.at<uchar>(j, i));
        }
    }
    vec = contrastImage(vec, src.rows, src.cols);
    n = 0;
    for (int j = 0; j < src.rows; j++) {
        for (int i = 0; i < src.cols; i++) {
            src.at<uchar>(j, i) = vec[n++];
        }
    }
    cv::imshow("second", src);
    cv::waitKey(0);

    show_histogram("image2 hist", src);

    cv::waitKey();

    #endif
}
