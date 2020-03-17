// Copyright 2020 Savkin Yuriy
#include <omp.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "./radix_sort_simple_merge_double.h"

TEST(Radix_Sort, Simple_Test) {
    double a[] = {1, -2, 0.5, 128.3, 0, 654, -22222222, 88.88, -3777};
    radixSortForDouble(a, 9);
}

TEST(Radix_Sort, Test_With_Random_Values) {
    std::vector<double> v = getRandomVector(100);
    std::vector<double> w(v);

    radixSortForDouble(v.data(), v.size());
    std::sort(w.begin(), w.end());

    EXPECT_EQ(w, v);
}

TEST(Radix_Sort, Test_With_Negative_Values) {
    std::vector<double> v = getRandomVector2(100);
    std::vector<double> w(v);

    radixSortForDouble(v.data(), v.size());
    std::sort(w.begin(), w.end());

    EXPECT_EQ(w, v);
}

TEST(Radix_Sort, Test_With_Many_Parts) {
    std::vector<double> v = getRandomVector2(100);
    std::vector<double> w(v);

    radixSortForDouble(v.data(), v.size(), 24);
    std::sort(w.begin(), w.end());

    EXPECT_EQ(w, v);
}

TEST(Radix_Sort, Test_With_1_Element) {
    std::vector<double> v = getRandomVector(1);
    std::vector<double> w(v);

    radixSortForDouble(v.data(), v.size(), 4);
    std::sort(w.begin(), w.end());

    EXPECT_EQ(w, v);
}

TEST(Radix_Sort, Test_With_Irregular_Parameters) {
    std::vector<double> v = getRandomVector(101);
    std::vector<double> w(v);

    radixSortForDouble(v.data(), v.size(), 7);
    std::sort(w.begin(), w.end());

    EXPECT_EQ(w, v);
}

TEST(Radix_Sort, Test_With_1_Thread) {
    std::vector<double> v = getRandomVector(100);
    std::vector<double> w(v);

    radixSortForDouble(v.data(), v.size(), 1);
    std::sort(w.begin(), w.end());

    EXPECT_EQ(w, v);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
