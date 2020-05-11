// Copyright 2020 Korobeinikov Aleksei
#include <gtest/gtest.h>
#include <omp.h>
#include <tbb/tbb.h>
#include <time.h>
#include <vector>
#include "../../modules/task_3/korobeinikov_a_quick_sort/quick_sort.h"


TEST(Quick_Parallel_tbb, TestParallelSort) {
    int n = 100000;
    double* arr = new double[n];
    getRandomArray(arr, n);
    tbb::tick_count start = tbb::tick_count::now();
    TbbParallelSort(arr, n, 8);
    tbb::tick_count finish = tbb::tick_count::now();
    // std::cout << (finish - start).seconds() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_tbb, TestParallelSortWithOddThreads) {
    int n = 100000;
    double* arr = new double[n];
    getRandomArray(arr, n);
    tbb::tick_count start = tbb::tick_count::now();
    TbbParallelSort(arr, n, 5);
    tbb::tick_count finish = tbb::tick_count::now();
    // std::cout << (finish - start).seconds() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_tbb, TestParallelSortWithOddSize) {
    int n = 34859;
    double* arr = new double[n];
    getRandomArray(arr, n);
    tbb::tick_count start = tbb::tick_count::now();
    TbbParallelSort(arr, n, 8);
    tbb::tick_count finish = tbb::tick_count::now();
    // std::cout << (finish - start).seconds() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_tbb, TestWithReverseOrder) {
    int n = 92832;
    double* arr = new double[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = n - i;
    }
    tbb::tick_count start = tbb::tick_count::now();
    TbbParallelSort(arr, n, 7);
    tbb::tick_count finish = tbb::tick_count::now();
    // std::cout << (finish - start).seconds() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_tbb, TestWithZeros) {
    int n = 9999;
    double* arr = new double[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
    tbb::tick_count start = tbb::tick_count::now();
    TbbParallelSort(arr, n, 6);
    tbb::tick_count finish = tbb::tick_count::now();
    // std::cout << (finish - start).seconds() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
