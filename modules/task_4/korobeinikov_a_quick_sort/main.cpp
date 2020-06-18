// Copyright 2020 Korobeinikov Aleksei
#include <gtest/gtest.h>
#include <chrono>
#include <time.h>
#include <vector>
#include <iostream>
#include "../../modules/task_4/korobeinikov_a_quick_sort/quick_sort.h"


TEST(Quick_Parallel_std, StdParSort) {
    int n = 1000000;
    double* arr = new double[n];
    getRandomArray(arr, n);
    auto begin = std::chrono::steady_clock::now();
    ParallelSort(arr, n, 8);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << elapsed_ms.count() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_std, StdOddThreads) {
    int n = 1000000;
    double* arr = new double[n];
    getRandomArray(arr, n);
    auto begin = std::chrono::steady_clock::now();
    ParallelSort(arr, n, 7);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << elapsed_ms.count() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_std, StdEvenThreads) {
    int n = 1000000;
    double* arr = new double[n];
    getRandomArray(arr, n);
    auto begin = std::chrono::steady_clock::now();
    ParallelSort(arr, n, 6);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << elapsed_ms.count() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_std, StdTestParallelSortWithOddSize) {
    int n = 34859;
    double* arr = new double[n];
    getRandomArray(arr, n);
    auto begin = std::chrono::steady_clock::now();
    ParallelSort(arr, n, 4);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << elapsed_ms.count() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_std, StdTestWithReverseOrder) {
    int n = 92832;
    double* arr = new double[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = n - i;
    }
    auto begin = std::chrono::steady_clock::now();
    ParallelSort(arr, n, 3);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << elapsed_ms.count() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

TEST(Quick_Parallel_std, StdTestWithZeros) {
    int n = 9999;
    double* arr = new double[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = 0;
    }
    auto begin = std::chrono::steady_clock::now();
    ParallelSort(arr, n, 5);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << elapsed_ms.count() << '\n';
    ASSERT_EQ(1, checkCorrectnessOfSort(arr, n));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
