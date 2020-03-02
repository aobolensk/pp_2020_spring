// Copyright 2020 Obolenskiy Arseniy
#include <gtest/gtest.h>
#include <omp.h>
#include "./gaussian_image_filtering.h"

TEST(Gaussian_Image_Filtering_seq, Can_Filter_Small_Image) {
    const int width = 10;
    const int height = 10;

    Image img = generateRandomImage(width, height);
    Image res = gaussianFilter(img, width, height);

    ASSERT_NE(res, img);
}

TEST(Gaussian_Image_Filtering_seq, Can_Handle_Empty_Image) {
    const int width = 0;
    const int height = 0;

    Image img = generateRandomImage(width, height);

    ASSERT_EQ(img, gaussianFilter(img, width, height));
}

TEST(Gaussian_Image_Filtering_seq, Can_Handle_Images_With_Width_Less_Than_Kernel_Size) {
    const int width = 2;
    const int height = 50;

    Image img = generateRandomImage(width, height);

    ASSERT_NE(img, gaussianFilter(img, width, height));
}

TEST(Gaussian_Image_Filtering_seq, Can_Handle_Images_With_Height_Less_Than_Kernel_Size) {
    const int width = 50;
    const int height = 2;

    Image img = generateRandomImage(width, height);

    ASSERT_NE(img, gaussianFilter(img, width, height));
}

TEST(Gaussian_Image_Filtering_seq, Can_Handle_Incorrect_Image_Height) {
    const int width = 10;
    const int height = 10;

    Image img = generateRandomImage(width, height);

    ASSERT_ANY_THROW(gaussianFilter(img, width, height - 1));
}

TEST(Gaussian_Image_Filtering_seq, Can_Handle_Incorrect_Image_Width) {
    const int width = 10;
    const int height = 10;

    Image img = generateRandomImage(width, height);

    ASSERT_ANY_THROW(gaussianFilter(img, width + 1, height));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
