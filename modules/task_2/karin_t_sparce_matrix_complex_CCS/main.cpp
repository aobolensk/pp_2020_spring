// Copyright 2020 Karin Timofey
#include <gtest/gtest.h>
#include <vector>
#include "../../modules/task_2/karin_t_sparce_matrix_complex_CCS/sparce_matrix.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Sparce_Matrix, can_create_random_matrix) {
  ASSERT_NO_THROW(SparceMatrix(6, 9, 10));
}

TEST(Sparce_Matrix, can_not_create_with_negative_size) {
  ASSERT_ANY_THROW(SparceMatrix(-6, 9, 10));
  ASSERT_ANY_THROW(SparceMatrix(6, -9, 10));
  ASSERT_ANY_THROW(SparceMatrix(6, 9, -10));
}

TEST(Sparce_Matrix, can_not_create_with_big_not_null_number_) {
  ASSERT_ANY_THROW(SparceMatrix(3, 3, 10));
}

TEST(Sparce_Matrix, can_create_with_max_not_null_number_) {
  ASSERT_NO_THROW(SparceMatrix(3, 3, 9));
}

TEST(Sparce_Matrix, can_convert_from_standart) {
  std::vector<std::vector<std::complex<int>>> matr(5);
  for (int i = 0; i < 5; i++) {
     matr[i].resize(4);
     for (int j = 0; j < 4; j++) {
       matr[i][j] = std::complex<int>(i+1, j+1);
     }
  }
  SparceMatrix SM(matr);
  ASSERT_EQ(SM.nCol, 4);
  ASSERT_EQ(SM.nRow, 5);
  ASSERT_EQ(SM.val[7], std::complex<int>(3, 2));
}

TEST(Sparce_Matrix, can_not_convert_from_incorrect_matrix) {
  std::vector<std::vector<std::complex<int>>> matr(5);
  for (int i = 0; i < 5; i++) {
    matr[i].resize(i);
    for (int j = 0; j < i; j++) {
      matr[i][j] = std::complex<int>(i + 1, j + 1);
    }
  }
  ASSERT_ANY_THROW(SparceMatrix SM(matr));
}

TEST(Sparce_Matrix, can_create_from_vectors) {
  std::vector<std::complex<int>> val(7);
    val[0] = std::complex<int>(35, 0);
    val[1] = std::complex<int>(29, 0);
    val[2] = std::complex<int>(65, 0);
    val[3] = std::complex<int>(51, 0);
    val[4] = std::complex<int>(85, 0);
    val[5] = std::complex<int>(36, 0);
    val[6] = std::complex<int>(61, 0);
    ASSERT_NO_THROW(SparceMatrix Matrix(3, 4, val, { 0, 1, 0, 1, 2, 0, 1}, {2, 5, 7}));
    SparceMatrix Matrix(3, 4, val, { 0, 1, 0, 1, 2, 0, 1 }, { 2, 5, 7 });
    ASSERT_EQ(Matrix.val, val);
    ASSERT_EQ(Matrix.nCol, 3);
    ASSERT_EQ(Matrix.nRow, 4);
}

TEST(Sparce_Matrix, can_compare) {
  std::vector<std::complex<int>> val(7);
  val[0] = std::complex<int>(35, 0);
  val[1] = std::complex<int>(29, 0);
  val[2] = std::complex<int>(65, 0);
  val[3] = std::complex<int>(51, 0);
  val[4] = std::complex<int>(85, 0);
  val[5] = std::complex<int>(36, 0);
  val[6] = std::complex<int>(61, 0);
  SparceMatrix Matrix(3, 4, val, { 0, 1, 0, 1, 2, 0, 1 }, { 2, 5, 7 });
  SparceMatrix Eq(3, 4, val, { 0, 1, 0, 1, 2, 0, 1 }, { 2, 5, 7 });
  SparceMatrix NotEq(3, 4, val, { 0, 2, 0, 1, 2, 0, 1 }, { 2, 5, 7 });
  ASSERT_EQ(Matrix, Eq);
  ASSERT_FALSE(Matrix == NotEq);
}

TEST(Sparce_Matrix, can_transpose) {
  std::vector<std::complex<int>> val(7);
  val[0] = std::complex<int>(35, 0);
  val[1] = std::complex<int>(29, 0);
  val[2] = std::complex<int>(65, 0);
  val[3] = std::complex<int>(51, 0);
  val[4] = std::complex<int>(85, 0);
  val[5] = std::complex<int>(36, 0);
  val[6] = std::complex<int>(61, 0);
  SparceMatrix Matrix(3, 4, val, { 0, 1, 0, 1, 2, 0, 1 }, { 2, 5, 7 });
  SparceMatrix TrMatrix = Matrix.Transpose();
  ASSERT_EQ(TrMatrix.nCol, 4);
  ASSERT_EQ(TrMatrix.nRow, 3);
  ASSERT_EQ(TrMatrix.val[0], val[0]);
  ASSERT_EQ(TrMatrix.val[1], val[2]);
  ASSERT_EQ(TrMatrix.val[2], val[5]);
  ASSERT_EQ(TrMatrix.val[3], val[1]);
  ASSERT_EQ(TrMatrix.val[4], val[3]);
  std::vector<int> check_row_num = {0, 1, 2, 0, 1, 2, 1};
  std::vector<int> check_point = {3, 6, 7, 7};
  ASSERT_EQ(TrMatrix.row_number, check_row_num);
  ASSERT_EQ(TrMatrix.point, check_point);
}

TEST(Sparce_Matrix, can_multiplication_without_throw) {
  SparceMatrix A(5, 3, 5);
  SparceMatrix B(3, 5, 10);
  ASSERT_NO_THROW(A*B);
}

TEST(Sparce_Matrix, can_not_multiplication_with_wrong_size) {
  SparceMatrix A(5, 3, 5);
  SparceMatrix B(5, 5, 10);
  ASSERT_ANY_THROW(A * B);
}

TEST(Sparce_Matrix, can_multyplication) {
  std::vector<std::complex<int>> val(7);
  val[0] = std::complex<int>(35, 0);
  val[1] = std::complex<int>(29, 0);
  val[2] = std::complex<int>(65, 0);
  val[3] = std::complex<int>(51, 0);
  val[4] = std::complex<int>(85, 0);
  val[5] = std::complex<int>(36, 0);
  val[6] = std::complex<int>(61, 0);
  SparceMatrix A(3, 4, val, { 0, 1, 0, 1, 2, 0, 1}, {2, 5, 7});
  SparceMatrix B = A.Transpose();
  SparceMatrix C = A * B;
  ASSERT_EQ(C.nCol, 4);
  ASSERT_EQ(C.nRow, 4);
  ASSERT_EQ(C.val[0], std::complex<int>(6746, 0));
  ASSERT_EQ(C.val[1], std::complex<int>(6526, 0));
  ASSERT_EQ(C.val[2], std::complex<int>(5525, 0));
  ASSERT_EQ(C.val[3], std::complex<int>(6526, 0));
  ASSERT_EQ(C.val[4], std::complex<int>(7163, 0));
  ASSERT_EQ(C.val[5], std::complex<int>(4335, 0));
  ASSERT_EQ(C.val[6], std::complex<int>(5525, 0));
  ASSERT_EQ(C.val[7], std::complex<int>(4335, 0));
  ASSERT_EQ(C.val[8], std::complex<int>(7225, 0));
}



TEST(Sparce_Matrix, can_parallel_multyplication) {
  std::vector<std::complex<int>> val_A(5);
  val_A[0] = std::complex<int>(7, 0);
  val_A[1] = std::complex<int>(5, 0);
  val_A[2] = std::complex<int>(2, 0);
  val_A[3] = std::complex<int>(3, 0);
  val_A[4] = std::complex<int>(10, 0);
  SparceMatrix A(3, 5, val_A, { 0, 4, 2, 1, 3 }, { 2, 3, 5 });
  std::vector<std::complex<int>> val_B(5);
  val_B[0] = std::complex<int>(5, 0);
  val_B[1] = std::complex<int>(9, 0);
  val_B[2] = std::complex<int>(4, 0);
  val_B[3] = std::complex<int>(1, 0);
  val_B[4] = std::complex<int>(6, 0);
  SparceMatrix B(5, 3, val_B, { 0, 2, 1, 2, 1 }, { 1, 2, 3, 4, 5 });
  SparceMatrix C = ParMult(A, B);
  ASSERT_EQ(C.nCol, 5);
  ASSERT_EQ(C.nRow, 5);
  ASSERT_EQ(C.val[0], std::complex<int>(35, 0));
  ASSERT_EQ(C.val[1], std::complex<int>(25, 0));
  ASSERT_EQ(C.val[2], std::complex<int>(27, 0));
  ASSERT_EQ(C.val[3], std::complex<int>(90, 0));
  ASSERT_EQ(C.val[4], std::complex<int>(8, 0));
  ASSERT_EQ(C.val[5], std::complex<int>(3, 0));
  ASSERT_EQ(C.val[6], std::complex<int>(10, 0));
  ASSERT_EQ(C.val[7], std::complex<int>(12, 0));
}

TEST(Sparce_Matrix, values_are_equal) {
  SparceMatrix A(200, 200, 50);
  SparceMatrix B(200, 200, 50);

  SparceMatrix ResPar = ParMult(A, B);
  SparceMatrix ResSeq = A * B;

  ASSERT_EQ(ResSeq, ResPar);
}
