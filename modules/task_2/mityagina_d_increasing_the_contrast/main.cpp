// Copyright 2020 Mityagina Daria
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "../../../modules/task_2/mityagina_d_increasing_the_contrast/increasing_the_contrast.h"

void testing_lab(int width, int height) {
  // int num = 4;  // 22,8%
  // int num = 2;  // 13%
  int num = 3;  // 19%
  // int num = 5;  // 25%
  ASSERT_NO_THROW(contrast_increase(generate_im(width, height), width, height, num));
}

TEST(contrast_increase, cant_process_images_with_zero_size) {
  int height = 0, width = 0;
  int num = 1;

  ASSERT_ANY_THROW(contrast_increase(generate_im(width, height), width, height, num));
}

TEST(contrast_increase, cant_process_images_with_negative_size_1) {
  int height = -10, width = 10;
  int num = 1;

  ASSERT_ANY_THROW(contrast_increase(generate_im(width, height), width, height, num));
}

TEST(contrast_increase, cant_process_images_with_negative_size_2) {
  int height = 10, width = -10;
  int num = 1;

  ASSERT_ANY_THROW(contrast_increase(generate_im(width, height), width, height, num));
}

TEST(contrast_increase, min_is_calculated_correctly) {
  std::vector<int> input = generate_im(10, 10);

  ASSERT_EQ(*std::min_element(input.begin(), input.end()), minimum(&input));
}

TEST(contrast_increase, max_is_calculated_correctly) {
  std::vector<int> input = generate_im(10, 10);

  ASSERT_EQ(*std::max_element(input.begin(), input.end()), maximum(&input));
}

TEST(contrast_increase, simple_example) {
  std::vector<int> input = {2, 14, 5, 104, 50, 60, 26, 64, 9};
  std::vector<int> output = std::vector<int>(input);
  int num = 1;

  for (int i = 0; i < static_cast<int>(input.size()); i++) {
    output[i] = static_cast<int>(-5 + 2.5 * input[i]);
  }

  ASSERT_EQ(output, contrast_increase(input, 3, 3, num));
}

// TEST(contrast_increase, min_is_greater_then_max) {
//   ASSERT_ANY_THROW(use_formula(7, 2, 10));
// }

TEST(contrast_increase, check_size_10_10) {
  testing_lab(10, 10);
}

// TEST(contrast_increase, check_size_100_100) {
//   testing_lab(101, 73);
// }

// TEST(contrast_increase, check_size_10000_10000) {
//   testing_lab(10000, 10000);
// }

TEST(contrast_increase, check_size_5000_5000) {
  testing_lab(5000, 5000);
}

TEST(contrast_increase, check_size_1000_1000) {
  testing_lab(1000, 1000);
}

TEST(contrast_increase, check_size_256_256) {
  testing_lab(256, 256);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
