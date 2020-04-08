// Copyright 2020 Suslov Egor
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./suslov_e_radix_omp.h"

TEST(radix_sort_for_double, Test_sorter_1) {
    int size = 10001;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    double* tmp = new double[size];
    LSDParallelSorter(Array, tmp, size, 2500);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(radix_sort_for_double, Test_sorter_2) {
    int size = 10000;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    double* tmp = new double[size];
    LSDParallelSorter(Array, tmp, size, 2500);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(radix_sort_for_double, Test_paralell_sort_1) {
    int size = 10000;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    LSDParallelSortDouble(Array, size, 2);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(radix_sort_for_double, Test_paralell_sort_four_threads_2) {
    int size = 10001;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    LSDParallelSortDouble(Array, size, 2);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(radix_sort_for_double, Test_paralell_sort_two_threads_3) {
    int size = 12345;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    LSDParallelSortDouble(Array, size, 2);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

