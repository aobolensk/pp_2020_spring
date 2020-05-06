// Copyright 2020 Suslov Egor
#include <gtest/gtest.h>
#include <vector>
#include "tbb/tbb.h"
#include "tbb/parallel_sort.h"
#include "./suslov_e_radix_b_tbb.h"

TEST(suslov_e_radix_sort_for_double, Test_on_100_tbbsort) {
    int size = 100;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDParallelSortDouble(Array, size, 2);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(suslov_e_radix_sort_for_double, Test_on_10000_tbbsort) {
    int size = 10000;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    //  clock_t start = clock();
    LSDParallelSortDouble(Array, size, 2);
    //  clock_t end = clock();
    //  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    //  printf("The time: %f seconds\n", seconds);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(suslov_e_radix_sort_for_double, Test_on_10001_tbbsort) {
    int size = 10001;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDParallelSortDouble(Array, size, 2);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(suslov_e_radix_sort_for_double, Test_on_11111_tbbsort) {
    int size = 11111;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDParallelSortDouble(Array, size, 2);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(suslov_e_radix_sort_for_double, Test_on_12121_tbbsort) {
    int size = 12121;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDParallelSortDouble(Array, size, 2);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
