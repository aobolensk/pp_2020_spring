// Copyright 2020 Vikhrev Ivan
#include <gtest/gtest.h>
#include "sobel_edge_detection.h"

TEST(sequential_edge_detection, can_create_image) {
	imageU a;
	int b = -1;
	std::cout<< b << std::endl;
	ASSERT_EQ(a.cols, 0);
	ASSERT_EQ(a.rows, 0);
	ASSERT_EQ(a.size, 0);
}

TEST(sequential_edge_detection, can_create_image_with_two_parameters) {
	imageU a{ 2, 2 };
	std::vector<uint8_t> b{ 0,0,0,0 };
	ASSERT_EQ(a.cols, 2);
	ASSERT_EQ(a.rows, 2);
	ASSERT_EQ(a.size, 4);
	ASSERT_EQ(a.data.size(), 4);
	ASSERT_EQ(a.data, b);
}

TEST(sequential_edge_detection, can_create_image_with_three_parameters) {
	imageU a{ 1, 1, {1} };
	ASSERT_EQ(a.cols, 1);
	ASSERT_EQ(a.rows, 1);
	ASSERT_EQ(a.size, 1);
	ASSERT_EQ(a.data.size(), 1);
	ASSERT_EQ(a.data[0], 1);
}

TEST(sequential_edge_detection, can_copy_image) {
	imageU a{ 1, 1, {1} };
	imageU b{ a };
	ASSERT_EQ(a.cols, b.cols);
	ASSERT_EQ(a.rows, b.rows);
	ASSERT_EQ(a.size, b.rows);
	ASSERT_EQ(a.data, b.data);
}

TEST(sequential_edge_detection, sobel) {
	imageU a{ 3,3, {1, 1,1, 1, 1,1, 1, 1,1} };
	imageU res =  sobel(a);
	std::vector<uint8_t> b;
	b.assign(9, sqrt(18));
	res.print();
	ASSERT_EQ(res.data, b);
    
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}