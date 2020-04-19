// Copyright 2020 Korobeinikov Aleksei
#include <gtest/gtest.h>
#include <omp.h>
#include <time.h>
#include <vector>
#include "../../modules/task_2/korobeinikov_a_quick_sort/quick_sort.h"


TEST(Quick_Parallel_omp, TestParallelSort) {
    int n = 36458;
    std::vector <double> vec = getRandomVector(n);
    quickSortParallel(&vec, 8);

    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Parallel_omp, TestParallelAndSeqSort) {
    int n = 17332;
    std::vector <double> vec = getRandomVector(n);
    quickSortParallel(&vec, 10);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
    quickSort(0, n - 1, &vec);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Parallel_omp, TestSeqAndParallelSort) {
    int n = 10000;
    std::vector <double> vec = getRandomVector(n);
    quickSort(0, n - 1, &vec);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
    quickSortParallel(&vec, 8);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Parallel_omp, CanSortWithOddNumberOfThreads) {
    int n = 10000;
    int th = 5;
    std::vector <double> vec = getRandomVector(n);

    quickSortParallel(&vec, th);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Parallel_omp, CanSortWithEvenNumberOfThreads) {
    int n = 14566;
    int th = 4;
    std::vector <double> vec = getRandomVector(n);

    quickSortParallel(&vec, th);
    ASSERT_EQ(1, checkCorrectnessOfSort(&vec));
}

TEST(Quick_Parallel_omp, CanEvenAndOddSplit) {
    int n = 7768;
    int part1 = 2000;
    std::vector <double> vec = getRandomVector(n);
    std::vector <double> vec1(vec.begin(), vec.begin() + part1);
    std::vector <double> vec2(vec.begin() + part1, vec.end());
    quickSort(0, vec1.size() - 1, &vec1);
    quickSortParallel(&vec2, 6);
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    EvenSplitter(0, part1, n - part1, &vec1);
    OddSplitter(0, part1, n - part1, &vec1);
    std::vector <double> ans1;
    std::vector <double> ans2;
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (i % 2 == 0) {
            ans1.push_back(vec1[i]);
        } else {
            ans2.push_back(vec1[i]);
        }
    }
    ASSERT_EQ(1, checkCorrectnessOfSort(&ans1));
    ASSERT_EQ(1, checkCorrectnessOfSort(&ans2));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
