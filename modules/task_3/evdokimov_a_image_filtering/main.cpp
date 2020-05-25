// Copyright 2019 Evdokimov Artem
#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <iostream>
#include <vector>

#include "./image_filtering.h"

/* double LiToDouble(LARGE_INTEGER x) {
  double result = ((double)x.HighPart) * 4.294967296E9 + (double)((x).LowPart);
  return result;
}

double GetTime() {
  LARGE_INTEGER lpFrequency, lpPerfomanceCount;
  QueryPerformanceFrequency(&lpFrequency);
  QueryPerformanceCounter(&lpPerfomanceCount);
  return LiToDouble(lpPerfomanceCount) / LiToDouble(lpFrequency);
}

TEST(Filtering_Image, DISABLED_Gotta_Go_Fast) {
  // Arrange
  int rows = 10000;
  int columns = 10000;
  std::vector<int> kernel = {1, 2, 1, 2, 4, 2, 1, 2, 1};
  double t1, t2;
  // Action
  const std::vector<int> source = generateImage(rows, columns);
  const std::vector<int> tempImg = getTempImage(source, rows, columns);
  t1 = GetTime();
  std::vector<int> basicFunction =
      imageFiltering(tempImg, kernel, rows, columns);
  t2 = GetTime();
  std::cout << "seq : " << t2 - t1 << std::endl;
  t1 = GetTime();
  std::vector<int> tbbFunction = imageFilteringTBB(tempImg, rows, columns);
  t2 = GetTime();
  std::cout << "tbb : " << t2 - t1 << std::endl;
  // Assert
  ASSERT_EQ(basicFunction, tbbFunction);
}

TEST(Filtering_Image, DISABLED_Gotta_Go) {
  // Arrange
  int rows = 10000;
  int columns = 10000;
  std::vector<int> kernel = {1, 2, 1, 2, 4, 2, 1, 2, 1};
  // Action
  const std::vector<int> source = generateImage(rows, columns);
  const std::vector<int> tempImg = getTempImage(source, rows, columns);

  // Assert
  ASSERT_NO_THROW(imageFilteringTBB(tempImg, rows, columns));
} */

TEST(Filtering_Image, Exception_In_Generate_Image_With_Not_Equals_Attributes) {
  // Arrange
  int columns = 0;
  int rows = -1;
  // Assert
  ASSERT_ANY_THROW(generateImage(rows, columns));
}

TEST(Filtering_Image, Exception_In_Temp_Image_With_Not_Equals_Attributes) {
  // Arrange
  int columns = 0;
  int rows = -1;
  // Assert
  ASSERT_ANY_THROW(getTempImage(generateImage(rows, columns), rows, columns));
}

TEST(Filtering_Image, Exception_In_Filtering_With_Not_Equals_Attributes) {
  // Arrange
  int columns = 0;
  int rows = -1;
  std::vector<int> kernel = {1, 2, 1, 2, 4, 2, 1, 2, 1};
  // Assert
  ASSERT_ANY_THROW(
      imageFiltering(generateImage(rows, columns), kernel, rows, columns));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
