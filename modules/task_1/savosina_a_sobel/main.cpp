// Copyright 2020 Savosina Aleksandra

#include <vector>
#include <string>
#include "./savosina_a.h"
#include "gtest/gtest.h"

TEST(savosina_a_sobel, Can_Create_Empty_Picture) {
  mainImage tmp;
  ASSERT_EQ(tmp.height, 0);
  ASSERT_EQ(tmp.width, 0);
  ASSERT_EQ(tmp.size, 0);
}

TEST(savosina_a_sobel, Can_Create_Picture) {
  mainImage tmp{ 1, 1, {1} };
  ASSERT_EQ(tmp.height, 1);
  ASSERT_EQ(tmp.width, 1);
  ASSERT_EQ(tmp.size, 1);
}

TEST(savosina_a_sobel, Can_Create_2_Picture) {
  mainImage tmp{ 2, 2, {1, 2, 4, 3} };
  ASSERT_EQ(tmp.height, 2);
  ASSERT_EQ(tmp.width, 2);
  ASSERT_EQ(tmp.size, 4);
}

TEST(savosina_a_sobel, Can_Compare_Two_Pictures) {
  mainImage tmp1{ 1, 1, {5} };
  mainImage tmp2{ 1, 1, {7} };
  ASSERT_NE(tmp1, tmp2);
}

TEST(savosina_a_sobel, Can_Make_A_Copy) {
  mainImage tmp1{ 1, 1, {3} };
  mainImage tmp2{ tmp1 };
  ASSERT_EQ(tmp1, tmp2);
}

TEST(savosina_a_sobel, Can_Compare_Two_Same_Pictures) {
  mainImage tmp1{ 1, 1, {3} };
  mainImage tmp2{ 1, 1, {3} };
  ASSERT_EQ(tmp1, tmp2);
}

TEST(savosina_a_sobel, Can_Get_Random_Picture) {
  mainImage a;
  a.getRandom(2, 2);
  ASSERT_EQ(a.height, 2);
  ASSERT_EQ(a.width, 2);
  ASSERT_EQ(a.size, 4);
}

TEST(savosina_a_sobel, Can_Sobel) {
  mainImage tmp{ 3, 3, {1, 1, 1, 1, 1, 1, 1, 1, 1} };
  mainImage res = sobel(tmp);
  ASSERT_NE(tmp, res);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
