// Copyright 2018 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./suslov_e_batchers_sort.h"

/*TEST(suslov_e_radix_sort_for_double, Test_5) {
    int size = 100000000;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    clock_t start = clock();
    LSDParallelSortDouble(Array, size, 2);

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    printf("The time: %f seconds\n", seconds);
    ;
    //std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, 1);//CompareArrays(Array, Array_copy, size)
}*/

TEST(radix_sort_for_double, Test_paralell_threads_1) {
    int size = 10000;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    LSDParallelSortDouble(Array, size, 2);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(radix_sort_for_double, Test_paralell_sort_threads_2) {
    int size = 10001;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    LSDParallelSortDouble(Array, size, 2);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(radix_sort_for_double, Test_paralell_sort_threads_3) {
    int size = 5000;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    LSDParallelSortDouble(Array, size, 2);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(radix_sort_for_double, Test_paralell_sort_threads_4) {
    int size = 10003;
    double* Array = getRandomArray(size);
    double* Array_copy = array_double_copy(Array, size);
    LSDParallelSortDouble(Array, size, 2);
    std::sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(radix_sort_for_double, Test_paralell_sort_threads_5) {
    int size = 10002;
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
