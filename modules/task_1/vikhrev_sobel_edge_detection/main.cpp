// Copyright 2020 Vikhrev Ivan
#include <gtest/gtest.h>
#include "sobel_edge_detection.h"

TEST(sequential_edge_detection, can_create_image) {
	imageU a;
	ASSERT_EQ(a.cols, 0);
	ASSERT_EQ(a.rows, 0);
	ASSERT_EQ(a.size, 0);
}

TEST(sequential_edge_detection, can_create_image_with_two_parameters) {
	imageU a(2,2);
	ASSERT_EQ(a.cols, 2);
	ASSERT_EQ(a.rows, 2);
	ASSERT_EQ(a.size, 4);
	ASSERT_EQ(a.data.size(), 4);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}