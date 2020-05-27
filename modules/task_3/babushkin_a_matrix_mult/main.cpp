// Copyright 2020 Babushkin Alexey
#include <gtest/gtest.h>
#include <tbb/task_arena.h>
#include <tbb/task_scheduler_init.h>
#include <tbb/tick_count.h>

#include <cmath>
#include <vector>

#include "./matrix_mult.h"

void test(const int n) {
  mtrxmult::Matrix left = mtrxmult::random_matrix(n, n);
  mtrxmult::Matrix right = mtrxmult::random_matrix(n, n);

  mtrxmult::Matrix mult_res_seq = mtrxmult::multiply(left, right, SEQUENTIAL);

  int allowedThreads =
      std::floor(std::log2(tbb::this_task_arena::max_concurrency()));
  tbb::task_scheduler_init init(std::pow(2, allowedThreads));
  mtrxmult::Matrix mult_res_cannon = mtrxmult::multiply_cannon(&left, &right);

  ASSERT_TRUE(mult_res_cannon == mult_res_seq);
}

TEST(Matrix_Mult_Cann, Random_Matrx_20) { test(20); }
TEST(Matrix_Mult_Cann, Random_Matrx_50) { test(50); }
TEST(Matrix_Mult_Cann, Random_Matrx_100) { test(100); }
TEST(Matrix_Mult_Cann, Random_Matrx_150) { test(150); }

TEST(Matrix_Mult_Cann, DISABLED_Comparison) {
  mtrxmult::Matrix left = mtrxmult::Matrix(mtrxmult::random_matrix(1000, 1000));
  mtrxmult::Matrix right =
      mtrxmult::Matrix(mtrxmult::random_matrix(1000, 1000));

  auto start = tbb::tick_count::now();
  auto parll_res = mtrxmult::multiply(left, right, PARALLEL);
  auto end = tbb::tick_count::now();

  std::cout << "Parll time: "
            << tbb::tick_count::interval_t(end - start).seconds() << "s"
            << std::endl;

  int allowedThreads =
      std::floor(std::log2(tbb::this_task_arena::max_concurrency()));
  tbb::task_scheduler_init init(std::pow(2, allowedThreads));

  start = tbb::tick_count::now();
  auto cann_res = mtrxmult::multiply_cannon(&left, &right);
  end = tbb::tick_count::now();

  std::cout << "Cann time: "
            << tbb::tick_count::interval_t(end - start).seconds() << "s"
            << std::endl;

  ASSERT_TRUE(cann_res == parll_res);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
