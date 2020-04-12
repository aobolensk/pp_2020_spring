// Copyright 2020 Suslov Egor
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./suslov_e_sort_batcher.h"

TEST(suslov_e_radix_sort_for_double, Test_1) {
    int size = 1000;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    double* tmp = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDSortDouble(Array, tmp, size);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(suslov_e_radix_sort_for_double, Test_2) {
    int size = 100;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    double* tmp = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDSortDouble(Array, tmp, size);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(suslov_e_radix_sort_for_double, Test_3) {
    int size = 50;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    double* tmp = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDSortDouble(Array, tmp, size);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(suslov_e_radix_sort_for_double, Test_4) {
    int size = 10000;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    double* tmp = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDParallelSorter(Array, tmp, size, 1000);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(suslov_e_radix_sort_for_double, Test_5) {
    int size = 10001;
    double* Array = getRandomArray(size);
    double* Array_copy = new double[size];
    double* tmp = new double[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    LSDParallelSorter(Array, tmp, size, 1000);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

