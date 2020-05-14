// Copyright 2019 Evdokimov Artem
#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <iostream>
#include <vector>

#include "./image_filtering.h"

TEST(Filtering_Image, TBB_Function_Works) {
  // Arrange
  int rows = 10;
  int columns = 10;
  std::vector<int> kernel = {1, 2, 1, 2, 4, 2, 1, 2, 1};
  std::vector<int> source = generateImage(rows, columns);
  std::vector<int> basicFunction = imageFiltering(
      getTempImage(source, rows, columns), kernel, rows, columns);
  std::vector<int> tbbFunction = imageFilteringTBB(source, rows, columns);
  // Assert
  ASSERT_EQ(basicFunction, tbbFunction);
}

TEST(Filtering_Image, DISABLED_TBB_Function_Stress) {
  // Arrange
  int rows = 8000;
  int columns = 8000;
  std::vector<int> kernel = {1, 2, 1, 2, 4, 2, 1, 2, 1};
  std::vector<int> source = generateImage(rows, columns);
  // Assert
  ASSERT_NO_THROW(imageFilteringTBB(source, rows, columns));
}

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
  ASSERT_ANY_THROW(getTempImage({1, 2, 3, 4}, rows, columns));
}

TEST(Filtering_Image, Exception_In_Filtering_With_Not_Equals_Attributes) {
  // Arrange
  int columns = 0;
  int rows = -1;
  std::vector<int> kernel = {1, 2, 1, 2, 4, 2, 1, 2, 1};
  // Assert
  ASSERT_ANY_THROW(imageFiltering({1, 2, 3, 4}, kernel, rows, columns));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
