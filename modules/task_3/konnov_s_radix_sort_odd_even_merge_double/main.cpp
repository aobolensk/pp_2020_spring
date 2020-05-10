// Copyright 2020 Konnov Sergey
#define NOMINMAX
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <tbb/tick_count.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./radix_sort_odd_even_merge_double.h"

TEST(Radix_Sort_Odd_Even_Merge, Simple_Test) {
    std::vector<double> a = {0., 10., 1., 11., 2., 12., 3., 13., -499.921,
                            -478.018, -270.971, -318.089, -180.188, -253.165, 269.783, 85.646};
    std::vector<double> a1 = a;
    a = radixSortOddEvenMergeDoubleParallel(a, 2);
    std::sort(a1.begin(), a1.end());
    EXPECT_EQ(a, a1);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Small_Positive_Vector) {
    std::vector<double> vec1 = getRandomVector(20, 0, 500);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1, 8);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Small_Negative_Vector) {
    std::vector<double> vec1 = getRandomVector(8, -500, 0);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1, 8);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Large_Vector) {
    std::vector<double> vec1 = getRandomVector(1000, -500, 500);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1, 8);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Vector_With_One_Elem) {
    std::vector<double> vec1 = getRandomVector(1, -500000, 500000);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1, 8);
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Vector_With_Large_Numbers) {
    std::vector<double> vec1 = getRandomVector(1000, -500000, 500000);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1, 8);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

// TEST(Radix_Sort_Odd_Even_Merge, Speed_Test) {
//     for(int i = 1; i <= 16; i++) {
//         double minn = 293485234;
//         for (int j = 0; j < 5; j++) {
//             std::vector<double> vec1 = getRandomVector(5000000, -500, 500);
//             std::vector<double> vec2 = vec1;
//             tbb::tick_count t1 = tbb::tick_count::now();
//             vec1 = radixSortOddEvenMergeDoubleParallel(vec1, i);
//             tbb::tick_count t2 = tbb::tick_count::now();
//             double time = static_cast<double>((t2-t1).seconds());
//             minn = std::min(minn, time);
//         }
//         std::cout<<i<<" "<<minn<<"\n";
//     }
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
