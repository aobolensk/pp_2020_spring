// Copyright 2020 Myshkin Andrey
#include <gtest/gtest.h>
#include <numeric>
#include <utility>
#include <algorithm>
#include "../../../modules/task_2/myshkin_a_radix_sort_omp/radix_sort_double.h"

TEST(Senquential, Test_Numder_First) {
    const int length = 10;
    int sts = 0;
    int sts2 = 0;
    double *buffer = nullptr;
    double *buffer2 = nullptr;
    int num_threads = 5;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
        buffer2 = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
        ASSERT_EQ(sts, 0);
    }

    sts2 = getRandomArray(buffer, length, -1000.0, 1000.0);
    memcpy(buffer2, buffer, sizeof(double) * length);

    sts = RadixSort(buffer, length);
    sts2 = SortingCheck(buffer, length);

    sts = RadixSortOmp(buffer2, length, num_threads);
    sts2 = SortingCheck(buffer2, length);

    sts = ArrayComparison(buffer, buffer2, length);

    if (sts2 == -1) sts = -1;

    if (buffer) { free(buffer); buffer = nullptr; }
    if (buffer2) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}

TEST(Senquential, Test_Numder_Second) {
    const int length = 43;
    int sts = 0;
    int sts2 = 0;
    double *buffer = nullptr;
    double *buffer2 = nullptr;
    int num_threads = 43;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
        buffer2 = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
        ASSERT_EQ(sts, 0);
    }

    sts2 = getRandomArray(buffer, length, -2000.0, 2000.0);
    memcpy(buffer2, buffer, sizeof(double) * length);

    sts = RadixSort(buffer, length);
    sts2 = SortingCheck(buffer, length);

    sts = RadixSortOmp(buffer2, length, num_threads);
    sts2 = SortingCheck(buffer2, length);

    sts = ArrayComparison(buffer, buffer2, length);

    if (sts2 == -1) sts = -1;

    if (buffer) { free(buffer); buffer = nullptr; }
    if (buffer2) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}

TEST(Senquential, Test_Numder_Third) {
    const int length = 88;
    int sts = 0;
    int sts2 = 0;
    double *buffer = nullptr;
    double *buffer2 = nullptr;
    int num_threads = 2;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
        buffer2 = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
        ASSERT_EQ(sts, 0);
    }

    sts2 = getRandomArray(buffer, length, -3000.0, 3000.0);
    memcpy(buffer2, buffer, sizeof(double) * length);

    sts = RadixSort(buffer, length);
    sts2 = SortingCheck(buffer, length);

    sts = RadixSortOmp(buffer2, length, num_threads);
    sts2 = SortingCheck(buffer2, length);

    sts = ArrayComparison(buffer, buffer2, length);

    if (sts2 == -1) sts = -1;

    if (buffer) { free(buffer); buffer = nullptr; }
    if (buffer2) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}

TEST(Senquential, Test_Numder_Fourth) {
    const int length = 64;
    int sts = 0;
    int sts2 = 0;
    double *buffer = nullptr;
    double *buffer2 = nullptr;
    int num_threads = 4;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
        buffer2 = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
        ASSERT_EQ(sts, 0);
    }

    sts2 = getRandomArray(buffer, length, -4000.0, 4000.0);
    memcpy(buffer2, buffer, sizeof(double) * length);

    sts = RadixSort(buffer, length);
    sts2 = SortingCheck(buffer, length);

    sts = RadixSortOmp(buffer2, length, num_threads);
    sts2 = SortingCheck(buffer2, length);

    sts = ArrayComparison(buffer, buffer2, length);

    if (sts2 == -1) sts = -1;

    if (buffer) { free(buffer); buffer = nullptr; }
    if (buffer2) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}

TEST(Senquential, Test_Numder_Fifth) {
    const int length = 63;
    int sts = 0;
    int sts2 = 0;
    double *buffer = nullptr;
    double *buffer2 = nullptr;
    int num_threads = 3;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
        buffer2 = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
        ASSERT_EQ(sts, 0);
    }

    sts2 = getRandomArray(buffer, length, -5000.0, 5000.0);
    memcpy(buffer2, buffer, sizeof(double) * length);

    sts = RadixSort(buffer, length);
    sts2 = SortingCheck(buffer, length);

    sts = RadixSortOmp(buffer2, length, num_threads);
    sts2 = SortingCheck(buffer2, length);

    sts = ArrayComparison(buffer, buffer2, length);

    if (sts2 == -1) sts = -1;

    if (buffer) { free(buffer); buffer = nullptr; }
    if (buffer2) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

