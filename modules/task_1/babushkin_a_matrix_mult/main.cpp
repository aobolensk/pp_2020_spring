// Copyright 2020 Babushkin Alexey

#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "./matrix_mult.h"

void test(const int n) {
  mtrxmult::Matrix left = mtrxmult::random_matrix(n, n);
  mtrxmult::Matrix right = mtrxmult::random_matrix(n, n);
  right.column_storage();

  mtrxmult::Matrix mult_res_cannon = mtrxmult::multiply_cannon(left, right);

  right.row_storage();

  mtrxmult::Matrix mult_res_seq = mtrxmult::multiply(left, right);

  ASSERT_TRUE(mult_res_cannon.equals(mult_res_seq));
}

TEST(Matrix_Mult_Seq, Getters) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  ASSERT_EQ(test_matrix.get_rows(), 3);
  ASSERT_EQ(test_matrix.get_cols(), 3);
  ASSERT_EQ(test_matrix.get_size(), 9u);

  test_matrix.resize(4, 2);

  ASSERT_EQ(test_matrix.get_rows(), 4);
  ASSERT_EQ(test_matrix.get_cols(), 2);
  ASSERT_EQ(test_matrix.get_size(), 8u);
}

TEST(Matrix_Mult_Seq, Mult_Same_Size) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
  mtrxmult::Matrix mult_result(
      {30.0, 36.0, 42.0, 66.0, 81.0, 96.0, 102.0, 126.0, 150.0}, 3, 3);

  ASSERT_TRUE(
      mtrxmult::multiply(test_matrix, test_matrix_2).equals(mult_result));
}

TEST(Matrix_Mult_Seq, Mult_Diff_Size) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8}, 4, 2);
  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 7}, 2, 3);
  mtrxmult::Matrix mult_result(
      {9.0, 12.0, 17.0, 19.0, 26.0, 37.0, 29.0, 40.0, 57.0, 39.0, 54.0, 77.0},
      4, 3);

  ASSERT_TRUE(
      mtrxmult::multiply(test_matrix, test_matrix_2).equals(mult_result));
}

TEST(Matrix_Mult_Seq, Mult_Err) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  test_matrix.resize(4, 2);

  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  ASSERT_ANY_THROW(mtrxmult::multiply(test_matrix, test_matrix_2));
  ASSERT_ANY_THROW(mtrxmult::multiply(test_matrix, mtrxmult::Matrix()));
}

TEST(Matrix_Mult_Seq, Mult_Cannon_Rand_10x10) { test(10); }

TEST(Matrix_Mult_Seq, Mult_Cannon_Rand_40x40) { test(40); }

// Commented too speed up testing
// TEST(Matrix_Mult_Seq, Mult_Cannon_Rand_80x80) { test(80); }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
