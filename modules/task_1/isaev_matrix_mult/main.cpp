// Copyright 2020 Isaev Ilya

#include <gtest/gtest.h>
#include <iostream>
#include "../../../modules/task_1/isaev_matrix_mult/matrix_mult.h"

TEST(Matrix_Mult, Matrix_Gen_Throws_On_Negative_Size) {
    ASSERT_ANY_THROW(getRandomMatrix(-1));
}

TEST(Matrix_Mult, Throws_On_Wrong_Sizes) {
    auto mat1 = getRandomMatrix(2);
    auto mat2 = getRandomMatrix(3);
    ASSERT_ANY_THROW(naiveMultiplication(mat1, mat2));
}

TEST(Matrix_Mult, Naive_Multiplication_Is_Correct_Size_3x3) {
    Matrix mat1 = {{1.5, 1.5, 1.5},
                   {2.7, 2.7, 2.7},
                   {3.6, 3.6, 3.6}};
    Matrix mat2 = {{3.5, 3.5, 3.5},
                   {5.7, 5.7, 5.7},
                   {9.6, 9.6, 9.6}};
    Matrix answer = {{28.2, 28.2, 28.2},
                    {50.76, 50.76, 50.76},
                    {67.68, 67.68, 67.68}};
    auto res = naiveMultiplication(mat1, mat2);

    ASSERT_EQ(matrixComparison(res, answer), true);
}

TEST(Matrix_Mult, Block_Multiplication_Is_Correct_Size_3x3) {
    Matrix mat1 = {{1.5, 1.5, 1.5},
                   {2.7, 2.7, 2.7},
                   {3.6, 3.6, 3.6}};
    Matrix mat2 = {{3.5, 3.5, 3.5},
                   {5.7, 5.7, 5.7},
                   {9.6, 9.6, 9.6}};
    Matrix answer = {{28.2, 28.2, 28.2},
                    {50.76, 50.76, 50.76},
                    {67.68, 67.68, 67.68}};
    auto res = blockMultiplication(mat1, mat2);

    ASSERT_EQ(matrixComparison(res, answer), true);
}

TEST(Matrix_Mult, Block_And_Naive_Have_The_Same_Answer) {
    auto mat1 = getRandomMatrix(5);
    auto mat2 = getRandomMatrix(5);
    ASSERT_EQ(matrixComparison(naiveMultiplication(mat1, mat2), blockMultiplication(mat1, mat2)), true);
}
