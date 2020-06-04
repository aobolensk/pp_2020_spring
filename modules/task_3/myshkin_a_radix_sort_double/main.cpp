// Copyright 2020 Myshkin Andrey

#include <gtest/gtest.h>
#include <tbb/tick_count.h>

#include "./radix_sort_tbb.h"

TEST(RadixSortTBB, Test_First) {
    double buffer[4] = { 2.3, 1.4, 6.4, -9.7 };
    int length = 4;
    int sts = 0;

    sts = RadixSort(buffer, length, 2);
    EXPECT_EQ(0, sts);
    sts = SortingCheck(buffer, length);
    EXPECT_EQ(0, sts);
}

TEST(RadixSortTBB, Test_Second) {
    double* buffer = nullptr;
    int length = 56;
    int sts = 0;

    buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));

    sts = getRandomArray(buffer, length, -0.5, 0.5);
    EXPECT_EQ(0, sts);
    sts = RadixSort(buffer, length, 2);
    EXPECT_EQ(0, sts);
    sts = SortingCheck(buffer, length);
    EXPECT_EQ(0, sts);

    if (buffer) { free(buffer); buffer = nullptr; }

    EXPECT_EQ(0, sts);
}

TEST(RadixSortTBB, Test_Third) {
    double buffer[7] = { 2.3, 1.4, 6.4, 9.7, 4.4, -1.4, -10.1 };
    int length = 7;
    int sts = 0;

    sts = RadixSort(buffer, 7, 4);
    EXPECT_EQ(0, sts);
    sts = SortingCheck(buffer, length);
    EXPECT_EQ(0, sts);
}

TEST(RadixSortTBB, Test_Fourth) {
    double* buffer = nullptr;
    int length = 100;
    int sts = 0;

    buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));

    sts = getRandomArray(buffer, length, -5000.0, 5000.0);
    EXPECT_EQ(0, sts);
    sts = RadixSort(buffer, length, 2);
    EXPECT_EQ(0, sts);
    sts = SortingCheck(buffer, length);
    EXPECT_EQ(0, sts);

    if (buffer) { free(buffer); buffer = nullptr; }

    EXPECT_EQ(0, sts);
}

TEST(RadixSortTBB, Test_Fifth) {
    double* buffer = nullptr;
    int length = 149;
    int sts = 0;

    buffer = reinterpret_cast<double*>(malloc(sizeof(double) * length));

    sts = getRandomArray(buffer, length, -1000.0, 1000.0);
    EXPECT_EQ(0, sts);
    sts = RadixSort(buffer, length, 3);
    EXPECT_EQ(0, sts);
    sts = SortingCheck(buffer, length);
    EXPECT_EQ(0, sts);

    if (buffer) { free(buffer); buffer = nullptr; }

    EXPECT_EQ(0, sts);
}

TEST(RadixSortTBB, Test_False_With_Length) {
    double buffer[4] = { 2.3, 1.4, 6.4, -9.7 };
    int length = -35;
    int sts = 0;

    sts = RadixSort(buffer, length, 2);
    EXPECT_EQ(-1, sts);
    sts = SortingCheck(buffer, length);
    EXPECT_EQ(-1, sts);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
