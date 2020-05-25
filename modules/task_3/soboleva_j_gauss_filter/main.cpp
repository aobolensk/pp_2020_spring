// Copyright 2020 Soboleva Julia
#include <gtest/gtest.h>
#include <time.h>
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

TEST(Gauss_Filter, Par_Filter_Throws1) {
  std::vector<uint8_t> a;
  int offset = -2;
  int pixelHeight = 129;
  ASSERT_ANY_THROW(ParFilter(a, offset, pixelHeight));
}

TEST(Gauss_Filter, ParFilter_Throws2) {
  std::vector<uint8_t> a(5);
  int offset = 137;
  int pixelHeight = 129;
  ASSERT_ANY_THROW(ParFilter(a, offset, pixelHeight));
}

TEST(Gauss_Filter, Par_Filter_Is_Correct1) {
    std::vector<uint8_t> a = { 0, 1, 2, 3, 4, 5 };
    std::vector<uint8_t> b = { 0, 1, 2, 3, 4, 5 };
    EXPECT_EQ(ParFilter(a, 2, 3, 7), b);
}

TEST(Gauss_Filter, Par_Filter_Is_Correct2) {
    std::vector<uint8_t> a = { 0, 0, 0, 0, 63, 0, 0, 0, 0 };
    std::vector<uint8_t> b = { 0, 0, 0, 0, 10, 0, 0, 0, 0 };
    EXPECT_EQ(ParFilter(a, 3, 3, 3), b);
}
/*
TEST(Gauss_Filter, Eff_Test) {
    int width = 2000, height = 5000;
    std::vector<uint8_t> img = GetRandMatrix(width, height);
    std::vector<uint8_t> a;
    clock_t start, end;

    start = clock();
    a = Filter(img, width, height);
    end = clock();
    double seconds = (static_cast<double>(end - start)) / CLOCKS_PER_SEC;
    std::cout<<"seq: "<<seconds<<"\n";
    start = clock();
    a = ParFilter(img, width, height, 61);
    end = clock();
    seconds = (static_cast<double>(end - start)) / CLOCKS_PER_SEC;
    std::cout << "par: "<<seconds << "\n";
    ASSERT_EQ(1,1);
}*/

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
