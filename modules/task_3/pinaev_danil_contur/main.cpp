// Copyright 2020 Pinaev Danil

#include <gtest/gtest.h>

#include <iostream>

#include "tbb/parallel_for.h"

#include "./contur.h"

TEST(Contur_ceq, Can_Make_One_Pixel_Image) {
    const int width = 1;
    const int height = 1;
    const size_t size = 9;

    Image img = generateRandomImage(width, height);

    ASSERT_EQ(img.data.size(), size);
}

TEST(Contur_ceq, Image_Size_Should_Be_Positive) {
    const int width = 0;
    const int height = 0;

    ASSERT_ANY_THROW(generateRandomImage(width, height));
}

TEST(Contur_ceq, Can_Take_Contur_Rand) {
    const int width = 10;
    const int height = 10;

    Image img = generateRandomImage(width, height);

    Image res = getContur(img);

    ASSERT_NE(res.data, img.data);
}

TEST(Contur_ceq, Can_Get_Contur_Weird_Size_1) {
    const int width = 1000;
    const int height = 1;

    Image img = generateRandomImage(width, height);

    Image res = getContur(img);

    ASSERT_NE(img.data, res.data);
}

TEST(Contur_ceq, Can_Get_Contur_Weird_Size_2) {
    const int width = 1;
    const int height = 1000;

    Image img = generateRandomImage(width, height);
    Image res = getContur(img);

    ASSERT_NE(img.data, res.data);
}

TEST(Contur_ceq, Can_Get_Patallel_Contur) {
    const int width = 640;
    const int height = 420;

    Image img = generateRandomImage(width, height);
    Image res = pattalelContur(img);

    ASSERT_NE(img.data, res.data);
}

TEST(Contur_ceq, Can_Get_Patallel_Contur_OCV) {
    const int width = 640;
    const int height = 420;

    Image img = generateRandomImage(width, height);
    Image res = pattalelContur(img);

    ASSERT_NE(img.data, res.data);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
