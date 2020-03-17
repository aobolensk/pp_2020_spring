// Copyright 2020 Zinkov Artem
#include <gtest/gtest.h>
#include <random>
#include <algorithm>
#include <vector>
#include "./gaussian_filter_hor.h"

TEST(Gaussian_Gilter_hor, Test_Zero_Pixels) {
  int rows = 0, cols = 0;

  std::vector<pixel> image = get_Random_Image(rows, cols);
  std::vector<pixel> copy(image);
  image = Gaussian_Filter_seq(image, rows, cols);

  ASSERT_EQ(image, copy);
}

TEST(Gaussian_Gilter_hor, Test_Different_Rows_and_Cols) {
  int rows = 10, cols = 200;
  std::vector<pixel> image = get_Random_Image(rows, cols);

  std::vector<pixel> res = Gaussian_Filter_seq(image, rows, cols);

  ASSERT_NE(image, res);
}

TEST(Gaussian_Gilter_hor, Test_Big_Image) {
  int rows = 300, cols = 300;
  std::vector<pixel> image = get_Random_Image(rows, cols);

  std::vector<pixel> res = Gaussian_Filter_seq(image, rows, cols);

  ASSERT_NE(res, image);
}

TEST(Gaussian_Gilter_hor, Test_Monochrome_Image) {
  int rows = 3, cols = 3;
  std::vector<pixel> image(rows * cols);
  for (auto& i : image) {
    i.r = 1;
    i.g = 1;
    i.b = 1;
  }
  std::vector<pixel> copy(image);

  image = Gaussian_Filter_seq(image, rows, cols);

  ASSERT_EQ(copy, image);
}

TEST(Gaussian_Gilter_hor, Test_One_Pixel) {
  int rows = 1, cols = 1;
  std::vector<pixel> image = get_Random_Image(rows, cols);
  std::vector<pixel> copy(image);

  image = Gaussian_Filter_seq(image, rows, cols);

  ASSERT_EQ(image, copy);
}

TEST(Gaussian_Gilter_hor, Test_Const_Image) {
  int rows = 3, cols = 3;
  std::vector<pixel> image(rows * cols);
  std::vector<pixel> image1(rows * cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      image[i * cols + j].r = 16 * GaussKernel[i][j];
      image[i * cols + j].g = 16 * GaussKernel[i][j];
      image[i * cols + j].b = 16 * GaussKernel[i][j];
    }
  }

  image1[0].r = image1[2].r = image1[6].r = image1[8].r = 25;
  image1[1].r = image1[3].r = image1[5].r = image1[7].r = 30;
  image1[4].r = 36;
  for (auto& i : image1) {
    i.b = i.r;
    i.g = i.r;
  }

  image = Gaussian_Filter_seq(image, rows, cols);

  ASSERT_EQ(image, image1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
