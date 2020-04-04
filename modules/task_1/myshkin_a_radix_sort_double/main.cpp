// Copyright 2020 Myshkin Andrey
#include <numeric>
#include <utility>
#include <algorithm>
#include "gtest/gtest.h"
#include "../../../modules/task_1/myshkin_a_radix_sort_double/radix_sort_double.h"


TEST(Senquential, Test_Numder_First) {
    const int length = 100;
    int sts = 0;
    double *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
    }

    sts = getRandomArray(buffer, length, -1000.0, 1000.0);

    sts = RadixSort(buffer, length);
    sts = SortingCheck(buffer, length);
    if (buffer) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}

TEST(Senquential, Test_Numder_Second) {
    const int length = 1000;
    int sts = 0;
    double *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
    }

    sts = getRandomArray(buffer, length, -1000.0, 1000.0);

    sts = RadixSort(buffer, length);
    sts = SortingCheck(buffer, length);
    if (buffer) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}

TEST(Senquential, Test_Numder_Third) {
    const int length = 1500;
    int sts = 0;
    double *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
    }

    sts = getRandomArray(buffer, length, -5000.0, 5000.0);

    sts = RadixSort(buffer, length);
    sts = SortingCheck(buffer, length);
    if (buffer) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}

TEST(Senquential, Test_Numder_Fourth) {
    const int length = 2000;
    int sts = 0;
    double *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
    }

    sts = getRandomArray(buffer, length, -2500.0, 2500.0);

    sts = RadixSort(buffer, length);
    sts = SortingCheck(buffer, length);
    if (buffer) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, 0);
}

TEST(Senquential, Test_Numder_Five) {
    const int length = 0;
    int sts = 0;
    double *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
    }

    sts = getRandomArray(buffer, length, -3000.0, 3000.0);

    sts = RadixSort(buffer, length);
    sts = SortingCheck(buffer, length);
    if (buffer) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, -1);
}

TEST(Senquential, Test_Numder_Six) {
    const int length = -15;
    int sts = 0;
    double *buffer = nullptr;

    if (length > 0) {
        buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    } else {
        sts = -1;
    }

    sts = getRandomArray(buffer, length, -1000.0, 1000.0);

    sts = RadixSort(buffer, length);
    sts = SortingCheck(buffer, length);
    if (buffer) { free(buffer); buffer = nullptr; }

    ASSERT_EQ(sts, -1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
