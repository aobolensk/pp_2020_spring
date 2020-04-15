// Copyright 2020 Konnov Sergey

#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./radix_sort_odd_even_merge_double.h"

TEST(Radix_Sort_Odd_Even_Merge, Simple_Test) {
    omp_set_num_threads(8);
    // std::vector<double> a = {0., 10., 1., 11., 2., 12., 3., 13.};
    std::vector<double> a = {0., 10., 1., 11., 2., 12., 3., 13., -499.921,
                            -478.018, -270.971, -318.089, -180.188, -253.165, 269.783, 85.646};
    std::vector<double> a1 = a;
    a = radixSortOddEvenMergeDoubleParallel(a);
    std::sort(a1.begin(), a1.end());
    // for(int i = 0; i < a.size(); i++)
    //     std::cout<<a[i]<<" ";
    // std::cout<<"\n";
    // for(int i = 0; i < a1.size(); i++)
    //     std::cout<<a1[i]<<" ";
    EXPECT_EQ(a, a1);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Small_Positive_Vector) {
    std::vector<double> vec1 = getRandomVector(20, 0, 500);
    // for(int i = 0; i < vec1.size(); i++)
    //     std::cout<<vec1[i]<<" ";
    // std::cout<<"\n";
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Small_Negative_Vector) {
    std::vector<double> vec1 = getRandomVector(8, -500, 0);
    // for(auto y: vec1)
    //     std::cout<<y<<" ";
    // std::cout<<"\n";
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1);
    std::sort(vec2.begin(), vec2.end());
    // std::cout<<vec1.size()<<" "<<vec2.size()<<"!!!!!!\n";
    EXPECT_EQ(vec1, vec2);
    // std::cout<<"?????";
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Large_Vector) {
    std::vector<double> vec1 = getRandomVector(1000, -500, 500);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Vector_With_One_Elem) {
    std::vector<double> vec1 = getRandomVector(1, -500000, 500000);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1);
    EXPECT_EQ(vec1, vec2);
}

TEST(Radix_Sort_Odd_Even_Merge, Can_Sort_Vector_With_Large_Numbers) {
    std::vector<double> vec1 = getRandomVector(1000, -500000, 500000);
    std::vector<double> vec2 = vec1;
    vec1 = radixSortOddEvenMergeDoubleParallel(vec1);
    std::sort(vec2.begin(), vec2.end());
    EXPECT_EQ(vec1, vec2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
