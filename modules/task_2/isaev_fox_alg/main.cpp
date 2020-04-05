// Copyright 2020 Isaev Ilya
#include <omp.h>
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_2/isaev_fox_alg/fox_alg.h"

TEST(Omp_Fox, Throws_On_NonEqual_Matrix) {
    auto a = getRandomMatrix(5);
    auto b = getRandomMatrix(6);

    ASSERT_ANY_THROW(foxAlgParallel(a, b, 2));
}

TEST(Omp_Fox, Parallel_Implementation_Is_Correct3x3) {
    Matrix mat1 = {{1.5, 1.5, 1.5},
                   {2.7, 2.7, 2.7},
                   {3.6, 3.6, 3.6}};
    Matrix mat2 = {{3.5, 3.5, 3.5},
                   {5.7, 5.7, 5.7},
                   {9.6, 9.6, 9.6}};
    Matrix answer = {{28.2, 28.2, 28.2},
                    {50.76, 50.76, 50.76},
                    {67.68, 67.68, 67.68}};
    auto res = foxAlgParallel(mat1, mat2, 2);

    ASSERT_EQ(matrixComparison(res, answer), true);
}

TEST(Omp_Fox, Parallel_And_Naive_Have_The_Same_Answer4x4) {
    auto mat1 = getRandomMatrix(4);
    auto mat2 = getRandomMatrix(4);

    auto res1 = naiveMultiplication(mat1, mat2);
    auto res2 = foxAlgParallel(mat1, mat2, 4);

    ASSERT_TRUE(matrixComparison(res1, res2));
}

TEST(Omp_Fox, Parallel_And_Block_Have_The_Same_Answer4x4) {
    auto mat1 = getRandomMatrix(4);
    auto mat2 = getRandomMatrix(4);

    auto res1 = blockMultiplication(mat1, mat2);

    auto res2 = foxAlgParallel(mat1, mat2, 4);

    ASSERT_TRUE(matrixComparison(res1, res2));
}


TEST(Omp_Fox, Parallel_And_Naive_Have_The_Same_Answer15x15) {
    auto mat1 = getRandomMatrix(15);
    auto mat2 = getRandomMatrix(15);

    auto res1 = naiveMultiplication(mat1, mat2);
    auto res2 = foxAlgParallel(mat1, mat2, 4);

    ASSERT_TRUE(matrixComparison(res1, res2));
}

TEST(Omp_Fox, Parallel_And_Block_Have_The_Same_Answer15x15) {
    auto mat1 = getRandomMatrix(15);
    auto mat2 = getRandomMatrix(15);

    // double t = omp_get_wtime();
    auto res1 = blockMultiplication(mat1, mat2);
    // std::cout << "BLOCK " << omp_get_wtime() - t << std::endl;

    // t = omp_get_wtime();
    auto res2 = foxAlgParallel(mat1, mat2, 4);
    // std::cout << "PARALLEL " << omp_get_wtime() - t << std::endl;

    ASSERT_TRUE(matrixComparison(res1, res2));
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
