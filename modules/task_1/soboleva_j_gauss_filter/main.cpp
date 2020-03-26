// Copyright 2020 Soboleva Julia
#include <gtest/gtest.h>
#include <random>
#include <vector>
#include "./soboleva_j_gauss_filter.h"

TEST(Gauss_Filter, Get_Index_Is_Correct) {
  int offset = 136;
  int i = 120;
  int j = 19;
  EXPECT_EQ(GetIndex(i, j, offset), 16339);
}

TEST(Gauss_Filter, Get_Rand_Matrix_Throws) {
  ASSERT_ANY_THROW(GetRandMatrix(-125, 4));
}

TEST(Gauss_Filter, Filter_Throws1) {
  std::vector<uint8_t> a;
  int offset = -2;
  int pixelHeight = 129;
  ASSERT_ANY_THROW(Filter(a, offset, pixelHeight));
}

TEST(Gauss_Filter, Filter_Throws2) {
  std::vector<uint8_t> a(5);
  int offset = 137;
  int pixelHeight = 129;
  ASSERT_ANY_THROW(Filter(a, offset, pixelHeight));
}

TEST(Gauss_Filter, Filter_Generates_Matrix) {
  std::vector<uint8_t> a;
  int offset = 10;
  int pixelHeight = 15;
  size_t s = 150;
  EXPECT_EQ(Filter(a, offset, pixelHeight).size(), s);
}

TEST(Gauss_Filter, Filter_Is_Correct1) {
  std::vector<uint8_t> a = { 0, 1, 2, 3, 4, 5 };
  std::vector<uint8_t> b = { 0, 1, 2, 3, 4, 5 };
  EXPECT_EQ(Filter(a, 2, 3, 1), b);
}

TEST(Gauss_Filter, Filter_Is_Correct2) {
  std::vector<uint8_t> a = { 0, 0, 0, 0, 63, 0, 0, 0, 0 };
  std::vector<uint8_t> b = { 0, 0, 0, 0, 10, 0, 0, 0, 0 };
  EXPECT_EQ(Filter(a, 3, 3, 1), b);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
