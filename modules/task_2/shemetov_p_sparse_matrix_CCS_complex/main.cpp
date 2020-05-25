// Copyright 2020 Shemetov Philipp

#include <omp.h>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "../../../modules/task_2/shemetov_p_sparse_matrix_CCS_complex/multi_matrix.h"




TEST(multi_matrix, TEST_WRONG_SIZE_FOR_MULTIPLY_MATRIX) {
     SparseMatrixCCS A(4, 2, 0.9);
     SparseMatrixCCS B(3, 2, 0.9);
     A = A.transpose();
     B = B.transpose();

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

TEST(multi_matrix, TEST_TIME_WITH_LARGE_NUMBERS_RANDOM_MATRIX) {
    SparseMatrixCCS A(30, 30, 0.8);
    SparseMatrixCCS B(30, 30, 0.8);
    A = A.transpose();
    B = B.transpose();

    // double start = omp_get_wtime();
    // SparseMatrixCCS result = SparseMatrixCCS::MultiplySparseMatrixParallel
    // (A, B);
    // double finish = omp_get_wtime();
    // printf("Time of quiksort without parallel %f in sec\n",finish-start);
    ASSERT_NO_FATAL_FAILURE(SparseMatrixCCS::MultiplySparseMatrixParallel(A, B));
}

TEST(multi_matrix, CAN_CREATE_SPARSE_CCS_MATRIX) {
    mtxComplex vecA = {{{7, -5}, {0}, {0}},
                        {{0}, {4, 3}, {0}},
                        {{0}, {0}, {-1, 1}}};
    SparseMatrixCCS A(vecA);
    A = A.transpose();

    std::vector<std::complex<double>> value {{7, -5}, {4, 3}, {-1, 1}};
    std::vector<int> row_index {0, 1, 2};
    std::vector<int> col_ptr {0, 1, 2, 3};
    SparseMatrixCCS B(3, 3, value, row_index, col_ptr);
    EXPECT_EQ(A, B);
}

TEST(multi_matrix, TEST_EQUAL_MULTIPLICATION_NOT_RANDOM_CCS_MATRIX) {
    mtxComplex vecA = {{{4, 3}, {0}, {9, 6}, {0}},
                        {{0}, {0}, {0}, {3}},
                        {{3, 5}, {6}, {0}, {4, 8}}};
    mtxComplex vecB ={{{3, 2}, {0}, {7}},
                        {{0} , {0}, {0}},
                        {{0}, {0}, {3, 9}},
                        {{3}, {0}, {4}}};
    SparseMatrixCCS A(vecA);
    SparseMatrixCCS B(vecB);
    A = A.transpose();
    B = B.transpose();
    mtxComplex vec3 = multiMatrix(vecA, vecB);
    SparseMatrixCCS expect(vec3);
    expect = expect.transpose();
    SparseMatrixCCS result = SparseMatrixCCS::MultiplySparseMatrixParallel(A, B);
    EXPECT_TRUE(expect == result);
}

TEST(multi_matrix, TEST_MATRIX_CONSISTS_OF_ZERO) {
    std::vector<std::complex<double>> valueA {};
    std::vector<int> row_indexA {};
    std::vector<int> col_ptrA {0, 0, 0, 0};
    SparseMatrixCCS A(3, 3, valueA, row_indexA, col_ptrA);

    std::vector<std::complex<double>> valueB {};
    std::vector<int> row_indexB {};
    std::vector<int> col_ptrB {0, 0, 0, 0};
    SparseMatrixCCS B(3, 3, valueB, row_indexB, col_ptrB);

    std::vector<std::complex<double>> valueExpect {};
    std::vector<int> row_indexExpect {};
    std::vector<int> col_ptrExpect {0, 0, 0, 0};
    SparseMatrixCCS expect(3, 3, valueExpect, row_indexExpect, col_ptrExpect);
    SparseMatrixCCS result = SparseMatrixCCS::MultiplySparseMatrixParallel(A, B);
    EXPECT_TRUE(expect == result);
}

TEST(multi_matrix, TEST_EQUAL_NOT_RANDOM_CCS_MATRIX_EXAMPLE) {
    std::vector<std::complex<double>> valueA {{4, 6}, {0, 4}, {3, 7},
                                                {4, 5}, {2, 1}};
    std::vector<int> row_indexA {0, 1, 1, 1, 2};
    std::vector<int> col_ptrA {0, 2, 3, 4, 5};
    SparseMatrixCCS A(3, 4, valueA, row_indexA, col_ptrA);

    std::vector<std::complex<double>> valueB {{0, 5}, {4, 7}, {0, 6}};
    std::vector<int> row_indexB {0, 3, 2};
    std::vector<int> col_ptrB {0, 2, 3};
    SparseMatrixCCS B(4, 2, valueB, row_indexB, col_ptrB);

    std::vector<std::complex<double>> valueExpect {{-30, 20}, {-20},
                                                   {1, 18}, {-30, 24}};
    std::vector<int> row_indexExpect {0, 1, 2, 1};
    std::vector<int> col_ptrExpect {0, 3, 4};
    SparseMatrixCCS expect(3, 2, valueExpect, row_indexExpect, col_ptrExpect);
    SparseMatrixCCS result = SparseMatrixCCS::MultiplySparseMatrixParallel(A, B);
    EXPECT_TRUE(expect == result);
}

TEST(multi_matrix, TEST_EQUAL_NOT_RANDOM_CCS_MATRIX_EXAMPLE_2) {
    std::vector<std::complex<double>> valueA {{4}, {3}, {5}, {3}, {7}};
    std::vector<int> row_indexA {0, 1, 1, 0, 2};
    std::vector<int> col_ptrA {0, 2, 3, 5};
    SparseMatrixCCS A(3, 3, valueA, row_indexA, col_ptrA);

    std::vector<std::complex<double>> valueB {{7}, {2}, {2}, {3}};
    std::vector<int> row_indexB {0, 2, 1, 1};
    std::vector<int> col_ptrB {0, 2, 3, 4};
    SparseMatrixCCS B(3, 3, valueB, row_indexB, col_ptrB);

    std::vector<std::complex<double>> valueExpect {{34}, {21}, {14}, {10},
                                                   {15}};
    std::vector<int> row_indexExpect {0, 1, 2, 1, 1};
    std::vector<int> col_ptrExpect {0, 3, 4, 5};
    SparseMatrixCCS expect(3, 3, valueExpect, row_indexExpect, col_ptrExpect);
    SparseMatrixCCS result = SparseMatrixCCS::MultiplySparseMatrixParallel(A, B);
    EXPECT_TRUE(expect == result);
}





int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
