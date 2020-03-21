// Copyright 2020 Repin Vladimir

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./radix_sort.h"

TEST(Radix_Sort, Small_Array_One_Part_Correct_Sorting) {
    std::vector<double> v = {15.33, -0.4, 615.561, -33.87, 11,
                             90.158, -93.06, 2.55, -8555555, 588.7};
    std::vector<double> w(v);
    double *test = new double[10];
    OddEvenMergeSort(v.data(), test, v.size(), 10);
    delete[] test;
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}
TEST(Radix_Sort, Small_Array_Multiple_Parts_Correct_Sorting) {
    std::vector<double> v = { 15.33, -0.4, 615.561, -33.87, 11,
                              90.158, -93.06, 2.55, -8555555, 588.7 };
    std::vector<double> w(v);
    double *test = new double[10];
    OddEvenMergeSort(v.data(), test, v.size(), 2);
    delete[] test;
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}
TEST(Radix_Sort, One_Element_Array_Correct_Sorting) {
    std::vector<double> v = {15.33};
    std::vector<double> w(v);
    double *test = new double[1];
    OddEvenMergeSort(v.data(), test, v.size(), 1);
    delete[] test;
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}

TEST(Radix_Sort, Large_Array_One_Part_Correct_Sorting) {
    std::vector<double> v = GetRandomVector(1000000);
    double *test = new double[1000000];
    std::vector<double> w(v);
    OddEvenMergeSort(v.data(), test, v.size(), 1000000);
    delete[] test;
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}
TEST(Radix_Sort, Large_Array_Multiple_Part_Correct_Sorting) {
    std::vector<double> v = GetRandomVector(1000000);
    double *test = new double[1000000];
    std::vector<double> w(v);
    OddEvenMergeSort(v.data(), test, v.size(), 10000);
    delete[] test;
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
