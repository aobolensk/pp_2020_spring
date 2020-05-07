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
  ASSERT_EQ(vec.size(), static_cast<unsigned int>(9));
}

TEST(Bin_image_segmentation, empty_space_small) {
  std::vector<int> vec = Generate_pic(5, 5);
  std::vector<int> res = Segmentation(vec, 5);
  bool eq = 1;
  for (size_t i = 0; i < 25; i++) {
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
    } else {
      if ((res[i] != res[i - 10] && res[i - 10] != 0)
        && (res[i] != res[i + 10] && res[i + 10] != 0)
        && (res[i] != res[i - 1] && res[i - 1] != 0)
        && (res[i] != res[i + 1] && res[i + 1] != 0)) {
        corr = 0;
        break;
      }
    }
  }
  ASSERT_EQ(1, corr);
}

TEST(Bin_image_segmentation, correctness_rectangle) {
  int w = 9;
  std::vector<int> vec = Generate_pic(w, 20);
  std::vector<int> res = Segmentation(vec, w);
  bool corr = 1;
  for (std::size_t i = static_cast<std::size_t>(w + 1); i < static_cast<std::size_t>(20 * w - w - 1); i++) {
    if (res[i] == 0) continue;
    if (i % w == 0) {
      if (res[i] != res[i - w] && res[i - w] != 0
        && res[i] != res[i + w] && res[i + w] != 0) {
        corr = 0;
        break;
      }
    } else {
      if ((res[i] != res[i - w] && res[i - w] != 0)
        && (res[i] != res[i + w] && res[i + w] != 0)
        && (res[i] != res[i - 1] && res[i - 1] != 0)
        && (res[i] != res[i + 1] && res[i + 1] != 0)) {
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
