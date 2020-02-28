// Copyright 2020 Golubev Vladislav
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "./golubev_v_graham_scan.h"

TEST(Sequential_graham_scan, Test_1) {
  std::vector<std::pair<double, double> > check = generate_points(5);
  std::sort(check.begin(), check.end(),
            [&check](const std::pair<double, double>& a, const std::pair<double, double>& b) {
    double grad_a = get_polar_grad(a);
    double grad_b = get_polar_grad(b);

    if (grad_a < grad_b) {
      return true;
    } else if ((std::abs(grad_a - grad_b) <= 1e-15) && (get_polar_r(a) <= get_polar_r(b))) {
      return true;
    } else {
      return false;
    }
  });

  std::cout << check[1].first << std::endl;
  ASSERT_EQ(1, 1);
}

TEST(Sequential_graham_scan, Test_2) {
  ASSERT_EQ(1, 1);
}

TEST(Sequential_graham_scan, Test_3) {
  ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
