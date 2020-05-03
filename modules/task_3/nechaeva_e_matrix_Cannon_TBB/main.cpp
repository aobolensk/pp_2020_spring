// Copyright 2020 Nechaeva Ekaterina
#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <random>
#include <stack>
#include "../../../modules/task_3/nechaeva_e_matrix_Cannon_TBB/matrix_m_Cannon.h"

TEST(Matrix_Cannon_tbb, throw_when_num_th_zero) {
    matrix A = RandomMatrix(3);
    matrix B = RandomMatrix(3);

    ASSERT_ANY_THROW(AlgorithmCannonTBB(A, B, 0));
}

TEST(Matrix_Cannon_tbb, throw_when_different_size_mat) {
    matrix A = RandomMatrix(3);
    matrix B = RandomMatrix(4);

    ASSERT_ANY_THROW(AlgorithmCannonTBB(A, B, 4));
}

TEST(Matrix_Cannon_tbb, time_for_parallel) {
    matrix A = RandomMatrix(500);
    matrix B = RandomMatrix(500);

    double t1 = omp_get_wtime();
    matrix rez1 = BlockMulti(A, B, 10);
    t1 = omp_get_wtime() - t1;

    double t2 = omp_get_wtime();
    matrix rez2 = AlgorithmCannonTBB(A, B, 100);
    t2 = omp_get_wtime() - t2;

     std::cout<<"seq = " <<t1<<std::endl<<t2<<std::endl;

    ASSERT_TRUE(CompareMatrix(rez1, rez2));
}

TEST(Matrix_Cannon_tbb, correct_result_mat_size_3) {
    matrix A = {{1.5, 1.7, 2.5},
                {3.7, 37.8, 2.5},
                {12.1, 2.0, 2.5}};
    matrix B = {{1.5, 1.7, 3.2},
                {3.7, 27.8, 3.2},
                {12.1, 2.0, 3.2}};
    matrix rez = {{38.79, 54.81, 18.24},
                {175.66, 1062.13, 140.8},
                {55.8, 81.17, 53.12}};

    ASSERT_TRUE(CompareMatrix(rez, AlgorithmCannonTBB(A, B, 4)));
}

TEST(Matrix_Cannon_tbb, correct_result_different_algorithms) {
    matrix A = RandomMatrix(4);
    matrix B = RandomMatrix(4);

    ASSERT_TRUE(CompareMatrix(NaiveMulti(A, B), AlgorithmCannonTBB(A, B, 4)));
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
