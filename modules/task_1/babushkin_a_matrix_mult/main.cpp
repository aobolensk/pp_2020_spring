// Copyright 2020 Babushkin Alexey

#include <gtest/gtest.h>

#include <string>

#include "./matrix_mult.h"

TEST(Matrix_Mult_Seq, Getters) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  ASSERT_EQ(test_matrix.get_rows(), 3);
  ASSERT_EQ(test_matrix.get_cols(), 3);
  ASSERT_EQ(test_matrix.get_size(), 9);

  test_matrix.resize(4, 2);

  ASSERT_EQ(test_matrix.get_rows(), 4);
  ASSERT_EQ(test_matrix.get_cols(), 2);
  ASSERT_EQ(test_matrix.get_size(), 8);
}

TEST(Matrix_Mult_Seq, To_String) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
  std::string result(
      "Matrix(3, 3)[ 1.000000, 2.000000, 3.000000, 4.000000, "
      "5.000000, 6.000000, 7.000000, 8.000000, 9.000000 ]");

  ASSERT_NO_THROW(test_matrix.to_string());
  ASSERT_EQ(test_matrix.to_string(), result);
}

TEST(Matrix_Mult_Seq, Mult_Same_Size) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
  mtrxmult::Matrix mult_result(
      {30.0, 36.0, 42.0, 66.0, 81.0, 96.0, 102.0, 126.0, 150.0}, 3, 3);

  ASSERT_EQ(test_matrix.multiply(test_matrix_2).get_data(),
            mult_result.get_data());
}

TEST(Matrix_Mult_Seq, Mult_Diff_Size) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8}, 4, 2);
  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 7}, 2, 3);
  mtrxmult::Matrix mult_result(
      {9.0, 12.0, 17.0, 19.0, 26.0, 37.0, 29.0, 40.0, 57.0, 39.0, 54.0, 77.0},
      4, 3);

  ASSERT_EQ(test_matrix.multiply(test_matrix_2).get_data(),
            mult_result.get_data());
}

TEST(Matrix_Mult_Seq, Mult_Err) {
  mtrxmult::Matrix test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  test_matrix.resize(4, 2);

  mtrxmult::Matrix test_matrix_2({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  ASSERT_ANY_THROW(test_matrix.multiply(test_matrix_2));
  ASSERT_ANY_THROW(test_matrix.multiply(mtrxmult::Matrix()));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
