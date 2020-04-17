// Copyright 2020 Babushkin Alexey

#include <gtest/gtest.h>
#include <omp.h>

#include <iostream>
#include <string>

#include "./matrix_mult.h"

void test(const int n) {
  mtrxmult::Matrix left = mtrxmult::random_matrix(n, n);
  mtrxmult::Matrix right = mtrxmult::random_matrix(n, n);

  mtrxmult::Matrix mult_res_seq = mtrxmult::multiply(left, right, SEQUENTIAL);

  omp_set_num_threads(4);
  mtrxmult::Matrix mult_res_cannon = mtrxmult::multiply_cannon(&left, &right);

  ASSERT_TRUE(mult_res_cannon == mult_res_seq);
}

TEST(Matrix_Mult_Cann, Getters) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  ASSERT_EQ(test_matrix.get_rows(), 3);
  ASSERT_EQ(test_matrix.get_cols(), 3);
  ASSERT_EQ(test_matrix.get_size(), 9u);

  test_matrix.resize(4, 2);

  ASSERT_EQ(test_matrix.get_rows(), 4);
  ASSERT_EQ(test_matrix.get_cols(), 2);
  ASSERT_EQ(test_matrix.get_size(), 8u);
}

TEST(Matrix_Mult_Cann, Mult_Same_Size) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
  mtrxmult::Matrix mult_result(
      {30.0, 36.0, 42.0, 66.0, 81.0, 96.0, 102.0, 126.0, 150.0}, 3, 3);

  ASSERT_TRUE(mtrxmult::multiply(test_matrix, test_matrix_2, SEQUENTIAL) ==
              mult_result);
}

TEST(Matrix_Mult_Cann, Mult_Diff_Size) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8}, 4, 2);
  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 7}, 2, 3);
  mtrxmult::Matrix mult_result(
      {9.0, 12.0, 17.0, 19.0, 26.0, 37.0, 29.0, 40.0, 57.0, 39.0, 54.0, 77.0},
      4, 3);

  ASSERT_TRUE(mtrxmult::multiply(test_matrix, test_matrix_2, SEQUENTIAL) ==
              mult_result);
}

TEST(Matrix_Mult_Cann, Mult_Err) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  test_matrix.resize(4, 2);

  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  ASSERT_ANY_THROW(mtrxmult::multiply(test_matrix, test_matrix_2, SEQUENTIAL));
  ASSERT_ANY_THROW(
      mtrxmult::multiply(test_matrix, mtrxmult::Matrix(), SEQUENTIAL));
}

TEST(Matrix_Mult_Cann, Mult_Cannon_Rand_10x10) { test(20); }

TEST(Matrix_Mult_Cann, Mult_Cannon_Rand_40x40) { test(40); }

TEST(Matrix_Mult_Cann, DISABLED_Comparison) {
  mtrxmult::Matrix test_matrix(mtrxmult::random_matrix(1000, 1000));
  mtrxmult::Matrix test_matrix_2(mtrxmult::random_matrix(1000, 1000));

  mtrxmult::Matrix res1, res2, res3;
  double time;

  time = omp_get_wtime();
  res3 = mtrxmult::multiply(test_matrix, test_matrix_2, SEQUENTIAL);
  std::cout << "Elapsed time default seq: " << omp_get_wtime() - time << "s"
            << std::endl;

  time = omp_get_wtime();
  res1 = mtrxmult::multiply(test_matrix, test_matrix_2, PARALLEL);
  std::cout << "Elapsed time default parll: " << omp_get_wtime() - time << "s"
            << std::endl;

  omp_set_num_threads(4);
  time = omp_get_wtime();
  res2 = mtrxmult::multiply_cannon(&test_matrix, &test_matrix_2);
  std::cout << "Elapsed time cannon parll: " << omp_get_wtime() - time << "s"
            << std::endl;

  ASSERT_TRUE(res1 == res2 && res2 == res3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
