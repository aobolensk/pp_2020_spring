// Copyright 2020 Kukushkina Ksenia

#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "./bin_image_segmentation.h"


TEST(Bin_image_segmentation, can_generate_image) {
  ASSERT_NO_THROW(Generate_pic(1000, 1000));
}

TEST(Bin_image_segmentation, negative_dim_image) {
  ASSERT_ANY_THROW(Generate_pic(-1, 100));
}

TEST(Bin_image_segmentation, image_dim) {
  std::vector<std::size_t> vec = Generate_pic(3, 3);
  ASSERT_EQ(vec.size(), static_cast<unsigned int>(9));
}

TEST(Bin_image_segmentation, empty_space_small) {
  std::size_t h = 30;
  std::size_t w = 20;
  std::vector<std::size_t> vec = Generate_pic(w, h);
  std::vector<std::size_t> res = Process(vec, w, h);
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
  std::size_t w = 99;
  std::size_t h = 100;
  std::vector<std::size_t> vec = Generate_pic(w, h);  // 999*1000
  std::vector<std::size_t> res = Process(vec, w, h);
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
  std::size_t w = 20;
  std::vector<std::size_t> vec = Generate_pic(w, w);
  std::vector<std::size_t> res = Process(vec, w, w);
  bool corr = 1;
  for (size_t i = w; i < w * w - w; i++) {
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
  if (corr == false)
    Output(res, w);
  ASSERT_EQ(true, corr);
}

TEST(Bin_image_segmentation, correctness_rectangle) {
  std::size_t w = 30;
  std::size_t h = 20;
  std::vector<std::size_t> vec = Generate_pic(w, h);
  std::vector<std::size_t> res = Process(vec, w, h);
  bool corr = 1;
  for (std::size_t i = w + 1; i < h * w - w - 1; i++) {
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
  if (corr == false)
    Output(res, w);
  ASSERT_EQ(true, corr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
