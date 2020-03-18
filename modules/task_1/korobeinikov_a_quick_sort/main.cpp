// Copyright 2020 Korobeinikov Aleksei
#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include <iostream>
#include "./quick_sort.h"

TEST(Quick_Sort_seq, Can_Sort_Zero_Array) {
    int n = 10000;
    std::vector <double> vec(n);
    vec[888] = 1;

    quickSort(0, n - 1, &vec);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Sort_seq, Can_Sort_Random_Array) {
    int n = 10000;
    std::vector <double> vec = getRandomVector(n);

    quickSort(0, n - 1, &vec);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Sort_seq, Can_Sort_With_Double_Elems) {
    int n = 10000;
    std::vector <double> vec = getRandomVector(n);
    vec[999] = -23.335;
    vec[560] = 2354.52;
    quickSort(0, n - 1, &vec);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Sort_seq, Can_Sort_With_Rotation_Elems) {
    int n = 10000;
    std::vector <double> vec = getRandomVector(n);
    for (int i = 1; i < n; i += 2) {
        vec[i] = -vec[i - 1];
    }

    quickSort(0, n - 1, &vec);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Sort_seq, Can_Sort_Full_Double_Array) {
    int n = 10000;
    std::vector <double> vec = getRandomVector(n);
    for (int i =0; i < n; ++i) {
        vec[i] *= 1.7475;
    }

    quickSort(0, n - 1, &vec);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
