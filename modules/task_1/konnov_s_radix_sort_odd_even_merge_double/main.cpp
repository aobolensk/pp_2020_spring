// Copyright 2020 Konnov Sergey

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./radix_sort_odd_even_merge_double.h"


TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Small_Positive_Vector) {
    std::vector<double> vec1 = getRandomVector(5, 0, 500);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDouble(vec1);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Small_Negative_Vector) {
    std::vector<double> vec1 = getRandomVector(5, -500, 0);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDouble(vec1);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Large_Vector) {
    std::vector<double> vec1 = getRandomVector(1000, -500, 500);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDouble(vec1);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Vector_With_One_Elem) {
    // std::vector<double> vec1 = {-2};
    std::vector<double> vec1 = getRandomVector(1, -500000, 500000);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDouble(vec1);
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Vector_With_Large_Numbers) {
    std::vector<double> vec1 = getRandomVector(1000, -500000, 500000);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDouble(vec1);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
