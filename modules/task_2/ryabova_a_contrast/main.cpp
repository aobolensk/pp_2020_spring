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
    int width2 = 200;
    int height = 100;

    Image img = randomImage(width1, height);

    ASSERT_ANY_THROW(contrastImage(img, width2, height));
}

#else
#include <omp.h>
#include <string>
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"

void show_histogram(std::string const& name, cv::Mat1b const& image) {
    int bins = 256;
    int histSize[] = { bins };

    float lranges[] = { 0, 256 };
    const float* ranges[] = { lranges };

    cv::Mat hist;
    int channels[] = { 0 };

    int const hist_height = 256;
    cv::Mat3b hist_image = cv::Mat3b::zeros(hist_height, bins);
    cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

    double max_val = 0;
    minMaxLoc(hist, 0, &max_val);

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

    cv::Mat img = cv::imread("C:/Users/User/Pictures/4.png");
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    std::vector <int> vec(img.rows * img.cols);
    cv::imshow("first", img);
    cv::waitKey(0);

    show_histogram("image1 hist", img);
    cv::waitKey(0);

    int n = 0;
    for (int j = 0; j < img.rows; j++) {
        for (int i = 0; i < img.cols; i++) {
            vec[n++] = static_cast<int>(img.at<uchar>(j, i));
        }
    }

    double time1 = omp_get_wtime();

    vec = contrastImage(vec, img.rows, img.cols);

    double time2 = omp_get_wtime();
    double timeFin = time2 - time1;
    std::cout << timeFin << std::endl;

    n = 0;
    for (int j = 0; j < img.rows; j++) {
        for (int i = 0; i < img.cols; i++) {
            img.at<uchar>(j, i) = vec[n++];
        }
    }
    cv::imshow("second", img);
    cv::waitKey(0);

    show_histogram("image2 hist", img);

    cv::waitKey();

    #endif
}
