// Copyright 2020 Shemetov Philipp

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "../../../modules/task_1/shemetov_p_sparse_matrix_CCS_complex/multi_matrix.h"




TEST(multi_matrix, TEST_WRONG_SIZE_FOR_MULTIPLY_MATRIX) {
     SparseMatrixCCS A(4, 2, 0.9);
     SparseMatrixCCS B(3, 2, 0.9);
     ASSERT_ANY_THROW(SparseMatrixCCS::MultiplySparseMatrix(A, B));
}

TEST(multi_matrix, TEST_WRONG_SIZE_M_MATRIX) {
    EXPECT_ANY_THROW(SparseMatrixCCS A(-1, 3, 0.7));
}

TEST(multi_matrix, TEST_WRONG_SIZE_N_MATRIX) {
    EXPECT_ANY_THROW(SparseMatrixCCS A(2, -1, 0.7));
}

TEST(multi_matrix, TEST_NOT_SPARSE_MATRIX) {
    EXPECT_ANY_THROW(SparseMatrixCCS A(4, 3, 0.4));
}

TEST(multi_matrix, CAN_CREATE_SPARSE_CCS_MATRIX) {
    mtxComplex vecA = {{{7, -5}, {0}, {0}},
                        {{0}, {4, 3}, {0}},
                        {{0}, {0}, {-1, 1}}};
    SparseMatrixCCS A(vecA);
    A = A.transpose();

    std::vector<std::complex<double>> value {{7, -5}, {4, 3}, {-1, 1}};
    std::vector<int> row_index {0, 1, 2};
    std::vector<int> col_ptr {0, 1, 2};
    SparseMatrixCCS B(3, 3, value, row_index, col_ptr);
    ASSERT_EQ(A, B);
}

TEST(multi_matrix, TEST_EQUAL_MULTIPLICATION_NOT_RANDOM_CCS_MATRIX) {
    mtxComplex vecA = {{{4, 3}, {0}, {9, 6}},
                        {{0}, {0}, {0}},
                        {{3, 5}, {6}, {0}}};
    mtxComplex vecB ={{{3, 2}, {0}, {7}},
                        {{0} , {0}, {0}},
                        {{0}, {0}, {3, 9}}};
    SparseMatrixCCS A(vecA);
    SparseMatrixCCS B(vecB);
    mtxComplex vec3 = multiMatrix(vecA, vecB);
    SparseMatrixCCS expect(vec3);
    expect = expect.transpose();
    SparseMatrixCCS result = SparseMatrixCCS::MultiplySparseMatrix(A, B)
            .transpose();
    EXPECT_TRUE(expect == result);
}

TEST(multi_matrix, TEST_EQUAL_NOT_RANDOM_CCS_MATRIX_EXAMPLE_2) {
    std::vector<std::complex<double>> valueA {{4, 6}, {0, 4}, {3, 7}, {4, 5},
                                              {3, 0}, {2, 1}};
    std::vector<int> col_indexA {0, 1, 2, 3, 2, 3};
    std::vector<int> row_ptrA {0, 2, 4, 6};
    SparseMatrixCCS A(3, 4, valueA, col_indexA, row_ptrA);

    std::vector<std::complex<double>> valueB {{0, 6}, {0, 5}, {4, 7}};
    std::vector<int> col_indexB {1, 0, 0};
    std::vector<int> row_ptrB {0, 1, 2, 2, 3};
    SparseMatrixCCS B(4, 2, valueB, col_indexB, row_ptrB);

    std::vector<std::complex<double>> valueExpect {{-20}, {-19, 48}, {1, 18},
                                                   {-36, 24}};
    std::vector<int> row_indexExpect {0, 1, 2, 0};
    std::vector<int> col_ptrExpect {0, 3, 4};
    SparseMatrixCCS expect(3, 2, valueExpect, row_indexExpect, col_ptrExpect);
    SparseMatrixCCS result = SparseMatrixCCS::MultiplySparseMatrix(A, B);
    result = result.transpose();
    EXPECT_TRUE(expect == result);
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
