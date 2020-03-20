// Copyright 2020 Kukushkina Ksenia

#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "./bin_image_segmentation.h"

TEST(Bin_image_segmentation, can_generate_image) {
  ASSERT_NO_THROW(Generate_pic(100, 100));
}

TEST(Bin_image_segmentation, negative_dim_image) {
  ASSERT_ANY_THROW(Generate_pic(-1, 100));
}

TEST(Bin_image_segmentation, image_dim) {
  std::vector<int> vec = Generate_pic(3, 3);
  ASSERT_EQ(vec.size(), 9);
}

TEST(Bin_image_segmentation, empty_space_small) {
  std::vector<int> vec = Generate_pic(10, 10);
  std::vector<int> res = Segmentation(vec, 10);
  bool eq = 1;
  for (size_t i = 0; i < 100; i++) {
    if ((vec[i] == 0 || res[i] == 0) && (vec[i] != res[i])) {
      eq = 0;
      break;
    }
  }
  ASSERT_EQ(1, eq);
}

TEST(Bin_image_segmentation, empty_space_large) {
  std::vector<int> vec = Generate_pic(99, 100);  // 999*1000
  std::vector<int> res = Segmentation(vec, 99);
  bool eq = 1;
  for (size_t i = 0; i < 9900; i++) {
    if ((vec[i] == 0 || res[i] == 0) && (vec[i] != res[i])) {
      eq = 0;
      break;
    }
  }
  ASSERT_EQ(1, eq);
}

TEST(Bin_image_segmentation, correctness_square) {
  std::vector<int> vec = Generate_pic(10, 10);
  std::vector<int> res = Segmentation(vec, 10);
  bool corr = 1;
  for (size_t i = 11; i < 89; i++) {
    if (res[i] == 0) continue;
    if (i % 10 == 0) {
      if (res[i] != res[i - 10] && res[i - 10] != 0
        && res[i] != res[i + 10] && res[i + 10] != 0) {
        corr = 0;
        break;
      }
      if (res[i] == res[i - 1]) {
        corr = 0;
        break;
      }
    } else {
      if (res[i] != res[i - 10] && res[i - 10] != 0
        && res[i] != res[i + 10] && res[i + 10] != 0
        && res[i] != res[i - 1] && res[i - 1] != 0
        && res[i] != res[i + 1] && res[i + 1] != 0) {
        corr = 0;
        break;
      }
    }
  }
  ASSERT_EQ(1, corr);
}

TEST(Bin_image_segmentation, correctness_rectangle) {
  std::vector<int> vec = Generate_pic(20, 10);
  std::vector<int> res = Segmentation(vec, 20);
  bool corr = 1;
  for (size_t i = 21; i < 179; i++) {
    if (res[i] == 0) continue;
    if (i % 20 == 0) {
      if (res[i] != res[i - 20] && res[i - 20] != 0
        && res[i] != res[i + 20] && res[i + 20] != 0) {
        corr = 0;
        break;
      }
      if (res[i] == res[i - 1]) {
        corr = 0;
        break;
      }
    } else {
      if (res[i] != res[i - 20] && res[i - 20] != 0
        && res[i] != res[i + 20] && res[i + 20] != 0
        && res[i] != res[i - 1] && res[i - 1] != 0
        && res[i] != res[i + 1] && res[i + 1] != 0) {
        corr = 0;
        break;
      }
    }
  }
  ASSERT_EQ(1, corr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
