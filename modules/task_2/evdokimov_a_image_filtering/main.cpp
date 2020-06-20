// Copyright 2019 Evdokimov Artem
#include <gtest/gtest.h>
#include <omp.h>

#include <iostream>
#include <vector>

#include "./image_filtering.h"


TEST(Filtering_Image, Image_FilteringOMP_Correct_Work) {
  // Arrange
  int columns = 2;
  int rows = 2;
  std::vector<int> m = {219, 136, 241, 223};
  // Act 207 174 226 209
  std::vector<int> randPic = getTempImage(m, rows, columns);
  std::vector<int> result = imageFilteringOMP(randPic, kernel(), rows, columns);
  // Result
  std::vector<int> expectedResult =
      imageFiltering(randPic, kernel(), rows, columns);
  // Assert
  ASSERT_EQ(result, expectedResult);
}

TEST(Filtering_Image, DISABLED_STRESS_TEST) {
  ASSERT_NO_THROW(
      imageFilteringOMP(getTempImage(generateImage(8000, 8000), 8000, 8000),
                        kernel(), 8000, 8000););
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
  // Assert
  ASSERT_ANY_THROW(imageFiltering({1, 2, 3, 4}, kernel(), rows, columns));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
