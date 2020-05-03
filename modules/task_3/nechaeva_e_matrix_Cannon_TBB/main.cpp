// Copyright 2020 Nechaeva Ekaterina
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <random>
#include <stack>
#include "../../../modules/task_3/nechaeva_e_matrix_Cannon_TBB/matrix_m_Cannon.h"


TEST(Matrix_Cannon_tbb, throw_when_different_size_mat) {
    matrix A = RandomMatrix(3);
    matrix B = RandomMatrix(4);

    ASSERT_ANY_THROW(AlgorithmCannonTBB(A, B));
}

TEST(Matrix_Cannon_tbb, time_for_parallel) {
    matrix A = RandomMatrix(100);
    matrix B = RandomMatrix(100);

    // auto t1 = tbb::tick_count::now();
    matrix rez1 = BlockMulti(A, B, 10);
    // auto time1 = (tbb::tick_count::now() - t1).seconds();

    // auto t2 = tbb::tick_count::now();
    matrix rez2 = AlgorithmCannonTBB(A, B);
    // auto time2 = (tbb::tick_count::now() - t2).seconds();
    // std::cout<<"seq = "<<time1<<std::endl<<"par = "<<time2<<std::endl;

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

    ASSERT_TRUE(CompareMatrix(rez, AlgorithmCannonTBB(A, B)));
}

TEST(Matrix_Cannon_tbb, correct_result_mat_size_4) {
    matrix A = {{3.5, 1.2, 3.5, 1.5},
                {-4.6, 6.1, 1.2, 2.3},
                {3.4, 5.6, 1.8, 2.6},
                {-4.6, 3.4, 4.8, 1.5}};
    matrix B = {{3.5, 2.3, 1.5, 4},
                {3.4, 5.2, 3.4, 1.2},
                {3.4, 2.3, 5.4, 1.2},
                {2.34, 2.3, 1.56, 4.567}};
    matrix rez = {{31.74, 25.79, 30.57, 26.4905},
                {14.102, 29.19, 23.908, 0.8641},
                {43.144, 47.06, 37.916, 34.3542},
                {15.29, 21.59, 32.92, -1.7095}};

    ASSERT_TRUE(CompareMatrix(rez, AlgorithmCannonTBB(A, B)));
}

TEST(Matrix_Cannon_tbb, correct_result_different_algorithms) {
    matrix A = RandomMatrix(5);
    matrix B = RandomMatrix(5);

    ASSERT_TRUE(CompareMatrix(NaiveMulti(A, B), AlgorithmCannonTBB(A, B)));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
