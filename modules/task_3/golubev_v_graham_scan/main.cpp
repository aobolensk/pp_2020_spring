// Copyright 2020 Golubev Vladislav
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include "../../../modules/task_3/golubev_v_graham_scan/golubev_v_graham_scan.h"

TEST(test, DISABLED_test) {
  std::size_t size = 10;
  auto area = get_rand_set(size);
  std::vector<std::pair<double, double> > check(size);
  TBB_scan scan(area);
}

TEST(test, scheduler) {
  tbb::task_scheduler_init init(5);
  tbb::task_group g;
  for (int i = 0; i < 5; ++i) {
    g.run([] {Sleep(1000); });
  }
  g.wait();
}

TEST(test, without_scheduler) {
  for (int i = 0; i < 3; ++i) {
    Sleep(1000);
  }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
