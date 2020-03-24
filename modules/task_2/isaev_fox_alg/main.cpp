// Copyright 2020 Isaev Ilya
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_2/isaev_fox_alg/fox_alg.h"

TEST(Omp_Fox, Throws_On_NonEqual_Matrix) {
    ASSERT_EQ(4+4, 2);
}

TEST(Omp_Fox, Parallel_Implementation_Is_Correct_Size_3x3) {
    ASSERT_EQ(4+4, 2);
}

TEST(Omp_Fox, Parallel_Implementation_Is_Correct_Size_15x15) {
    ASSERT_EQ(4+4, 2);
}

TEST(Omp_Fox, Parallel_And_Naive_Have_The_Same_Answer) {
    ASSERT_EQ(4+4, 2);
}

TEST(Omp_Fox, Parallel_And_Block_Have_The_Same_Answer) {
    ASSERT_EQ(4+4, 2);
}

TEST(Omp_Fox, AxB_Is_Not_BxA) {
    ASSERT_EQ(4+4, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
