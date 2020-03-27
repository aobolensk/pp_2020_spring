// Copyright 2020 Tonkov Alexei
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./odd_even_mergesort.h"

TEST(test_odd_even_mergesort, sort_10_elem) {
    std::vector<int> a = getRandomVector(14);
    std::vector<int> b = a;
    b = oddEvenSort(b, 14);
    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

TEST(test_odd_even_mergesort, sort_50_elem) {
    std::vector<int> a = getRandomVector(9);
    std::vector<int> b = a;
    b = oddEvenSort(b, 9);
    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

TEST(test_odd_even_mergesort, sort_100_elem) {
    std::vector<int> a = getRandomVector(8);
    std::vector<int> b = a;
    b = oddEvenSort(b, 8);
    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

TEST(test_odd_even_mergesort, sort_500_elem) {
    std::vector<int> a = getRandomVector(500);
    std::vector<int> b = a;
    b = oddEvenSort(b, 500);
    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

TEST(test_odd_even_mergesort, sort_10000_elem) {
    std::vector<int> a = getRandomVector(10000);
    std::vector<int> b = a;
    b = oddEvenSort(b, 10000);
    std::sort(a.begin(), a.end());
    ASSERT_EQ(a, b);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
