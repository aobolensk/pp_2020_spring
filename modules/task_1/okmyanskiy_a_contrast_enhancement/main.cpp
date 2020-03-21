// Copyright 2020 Okmyanskiy Andrey
#include <gtest/gtest.h>
#include <vector>
#include "./contrast_enhancement.h"

TEST(Sequential_Contrast_Enhancement, Test_Random_Matrix_Size_Zero) {
  const int matrixWidth = 15;
  const int matrixHeight = 0;

  ASSERT_ANY_THROW(getRandomMatrix(matrixWidth, matrixHeight));
}

TEST(Sequential_Contrast_Enhancement, Test_Random_Matrix_Size_Correctly) {
  const int matrixWidth = 10;
  const int matrixHeight = 10;

  ASSERT_NO_THROW(getRandomMatrix(matrixWidth, matrixHeight));
}

TEST(Sequential_Contrast_Enhancement, Test_Stretching_Minimum_Greather_Maximum) {
  const int min = 200;
  const int max = 50;
  const int value = 10;

  ASSERT_ANY_THROW(linearHistogramStretching(value, max, min));
}

TEST(Sequential_Contrast_Enhancement, Test_Stretching_Minimum_Or_Maximum_False) {
  const int min = -5;
  const int max = 260;
  const int value = 10;

  ASSERT_ANY_THROW(linearHistogramStretching(value, max, min));
}

TEST(Sequential_Contrast_Enhancement, Test_Check_Stretching_Correct) {
  const int min = 6;
  const int max = 158;
  const int value = 18;

  ASSERT_EQ(20, linearHistogramStretching(value, max, min));
}

TEST(Sequential_Contrast_Enhancement, Test_Result_Matrix_Size_Negative) {
  const int matrixWidth = 15;
  const int matrixHeight = -14;
  const std::vector<int> matrix(abs(matrixWidth * matrixHeight));

  ASSERT_ANY_THROW(getResultMatrix(matrix, matrixWidth, matrixHeight));
}

TEST(Sequential_Contrast_Enhancement, Test_Result_Matrix_Wrong_Size) {
  const int matrixWidth = 15;
  const int matrixHeight = 14;
  const std::vector<int> matrix(matrixWidth * matrixHeight + 1);

  ASSERT_ANY_THROW(getResultMatrix(matrix, matrixWidth, matrixHeight));
}

TEST(Sequential_Contrast_Enhancement, Test_Result_Matrix_Size_Correctly) {
  const int matrixWidth = 100;
  const int matrixHeight = 100;
  const std::vector<int> matrix = getRandomMatrix(matrixWidth, matrixHeight);

  ASSERT_NO_THROW(getResultMatrix(matrix, matrixWidth, matrixHeight));
}

TEST(Sequential_Contrast_Enhancement, Test_Check_Result_Matrix_Correct_3x4) {
  int width = 3, height = 4;
  std::vector<int> initial(width * height);
  std::vector<int> result(width * height);
  initial = { 6, 109, 196, 66, 122, 125, 233, 73, 43, 171, 183, 47 };

  for (int i = 0; i < width * height; i++) {
    result[i] = static_cast<int>(-6.74009f + 1.12335f * initial[i]);
  }
  ASSERT_EQ(result, getResultMatrix(initial, width, height));
}

TEST(Sequential_Contrast_Enhancement, Test_Check_Result_Matrix_Correct_4x4) {
    int width = 4, height = 4;
    std::vector<int> initial(width * height);
    std::vector<int> result(width * height);
    initial = { 166, 136, 173, 190, 203, 103, 135, 112, 11, 195, 244, 47, 244, 246, 144, 223 };

    for (int i = 0; i < width * height; i++) {
        result[i] = static_cast<int>(-11.936171f+ 1.085106f * initial[i]);
    }
    ASSERT_EQ(result, getResultMatrix(initial, width, height));
}

TEST(Sequential_Contrast_Enhancement, Test_Check_Result_Matrix_Correct_4x5) {
    int width = 4, height = 5;
    std::vector<int> initial(width * height);
    std::vector<int> result(width * height);
    initial = { 53, 217, 91, 175, 51, 83, 141, 150, 60, 149, 44,
        195, 250, 222, 144, 4, 30, 76, 147, 200 };

    for (int i = 0; i < width * height; i++) {
        result[i] = static_cast<int>(-4.146341f + 1.036585f * initial[i]);
    }
    ASSERT_EQ(result, getResultMatrix(initial, width, height));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
