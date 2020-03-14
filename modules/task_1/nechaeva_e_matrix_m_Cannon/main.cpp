// Copyright 2020 Nechaeva Ekaterina

#include <gtest/gtest.h>
#include <iostream>
#include "../../../modules/task_1/nechaeva_e_matrix_m_Cannon/matrix_m_Cannon.h"

TEST(Matrix_Cannon, matrix_with_negative_size) {
    ASSERT_ANY_THROW(RandomMatrix(0));
}

TEST(Matrix_Cannon, correct_compare_matrix) {
    matrix A = {{1.5, 1.7},
                {3.789, 37.8},
                {12.1234, 2.0}};
    matrix B = {{1.5, 1.7},
                {3.789, 37.8},
                {12.1234, 2.0}};

    ASSERT_TRUE(CompareMatrix(A, B));
}

TEST(Matrix_Cannon, correct_compare_different_matrix) {
    matrix A = RandomMatrix(3);
    matrix B = RandomMatrix(3);

    ASSERT_FALSE(CompareMatrix(A, B));
}

TEST(Matrix_Cannon, throw_when_naive_mult_with_different_size) {
    matrix A = RandomMatrix(3);
    matrix B = RandomMatrix(5);

    ASSERT_ANY_THROW(NaiveMulti(A, B));
}

TEST(Matrix_Cannon, correct_result_of_the_naive_multiplication) {
    matrix A = {{1.5, 1.7, 2.5},
                {3.7, 37.8, 2.5},
                {12.1, 2.0, 2.5}};
    matrix B = {{1.5, 1.7, 3.2},
                {3.7, 27.8, 3.2},
                {12.1, 2.0, 3.2}};
    matrix rez = {{38.79, 54.81, 18.24},
                {175.66, 1062.13, 140.8},
                {55.8, 81.17, 53.12}};

    ASSERT_TRUE(CompareMatrix(rez, NaiveMulti(A, B)));
}

TEST(Matrix_Cannon, correct_result_of_the_block_multiplication) {
    matrix A = {{1.5, 1.7, 2.5},
                {3.7, 37.8, 2.5},
                {12.1, 2.0, 2.5}};
    matrix B = {{1.5, 1.7, 3.2},
                {3.7, 27.8, 3.2},
                {12.1, 2.0, 3.2}};
    matrix rez = {{38.79, 54.81, 18.24},
                {175.66, 1062.13, 140.8},
                {55.8, 81.17, 53.12}};

    ASSERT_TRUE(CompareMatrix(rez, BlockMulti(A, B, 2)));
}

TEST(Matrix_Cannon, the_same_results_of_the_mult) {
    matrix A = RandomMatrix(3);
    matrix B = RandomMatrix(3);

    ASSERT_TRUE(CompareMatrix(NaiveMulti(A, B), BlockMulti(A, B, 2)));
}
