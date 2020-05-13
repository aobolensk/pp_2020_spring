// Copyright 2020 Repin Vladimir

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./radix_sort.h"

TEST(Radix_Sort, Small_Array_One_Thread_Correct_Sorting) {
    int th_num = 1;
    std::vector<double> v = { 15.33, -0.4, 615.561, -33.87, 11,
                              90.158, -93.06, 2.55, -8555555, 588.7 };
    std::vector<double> w(v);
    OddEvenMergeSortOMP(v.data(), v.size(), v.size()/th_num, th_num);
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}
TEST(Radix_Sort, Small_Array_Multiple_Thread_Correct_Sorting) {
    int th_num = 2;
    std::vector<double> v = { 15.33, -0.4, 615.561, -33.87, 11,
        90.158, -93.06, 2.55, -8555555, 588.7 };
    std::vector<double> w(v);
    OddEvenMergeSortOMP(v.data(), v.size(), v.size() / th_num, th_num);
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}
TEST(Radix_Sort, One_Element_Array_Correct_Sorting) {
    int th_num = 1;
    std::vector<double> v = {15.33};
    std::vector<double> w(v);
    OddEvenMergeSortOMP(v.data(), v.size(), v.size() / th_num, th_num);
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}

TEST(Radix_Sort, Large_Array_One_Thread_Correct_Sorting) {
    int th_num = 1;
    std::vector<double> v = GetRandomVector(100);
    std::vector<double> w(v);
    OddEvenMergeSortOMP(v.data(), v.size(), v.size()/th_num, 2);
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}
TEST(Radix_Sort, Large_Array_Multiple_Thread_Correct_Sorting) {
    int th_num = 2;
    std::vector<double> v = GetRandomVector(100);
    std::vector<double> w(v);
    OddEvenMergeSortOMP(v.data(), v.size(), v.size()/th_num, 2);
    std::sort(w.begin(), w.end());
    EXPECT_EQ(v, w);
}

// TEST(Radix_Sort, Showcase) {
//    int th_num = 4;
//    std::vector<double> v2 = GetRandomVector(100000000);
//    std::vector<double> v1(v2);
//
//    int t = clock();
//    OddEvenMergeSortOMP(v1.data(), v1.size(), v1.size() / th_num, 1);
//    double t_seq = (clock() - t) / 1000.0;
//    std::cout << "1thread_par = " << (t_seq) << "\n";
//    t = clock();
//    OddEvenMergeSortOMP(v2.data(), v2.size(), v2.size() / th_num, th_num);
//    double t_par = (clock() - t) / 1000.0;
//    std::cout << "Par = " << t_par << "\n";
//    std::cout << "Speedup = " << t_seq / t_par
//    << "with " << th_num << " threads.";
//    }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
