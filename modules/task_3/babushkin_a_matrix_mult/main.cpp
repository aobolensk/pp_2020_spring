// Copyright 2020 Babushkin Alexey
#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <vector>

#include "./matrix_mult.h"

TEST(Sample, Comparison) {
  mtrxmult::Matrix m1 = mtrxmult::Matrix(mtrxmult::random_matrix(300, 300));
  mtrxmult::Matrix m2 = mtrxmult::Matrix(mtrxmult::random_matrix(300, 300));

  auto start = tbb::tick_count::now();
  auto res1 = mtrxmult::multiply(m1, m2, SEQUENTIAL);
  auto end = tbb::tick_count::now();

  std::cout << "Seq time: "
            << tbb::tick_count::interval_t(end - start).seconds() << "s"
            << std::endl;

  start = tbb::tick_count::now();
  auto res2 = mtrxmult::multiply(m1, m2, PARALLEL);
  end = tbb::tick_count::now();

  std::cout << "Parll time: "
            << tbb::tick_count::interval_t(end - start).seconds() << "s"
            << std::endl;

  ASSERT_TRUE(res1 == res2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
