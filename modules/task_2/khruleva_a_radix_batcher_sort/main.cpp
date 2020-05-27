// Copyright 2020 Khruleva Anastasia
#include <omp.h>
#include <utility>
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <bitset>
#include <algorithm>
#include "gtest/gtest.h"
#include "../../../modules/task_2/khruleva_a_radix_batcher_sort/radix_batcher_sort.h"

#define BITS 8
#define N 10000
#define TESTS 10
#define THREADS 4

TEST(Radix_Batcher_Sort_OMP, Can_Sort_Properly) {
    omp_set_nested(1);
    int* array = new int[N];
    gen_rnd_arr(array, N, BITS);
    int* b = new int[N];
    duplicate_array(array, b, N);
    radix_batcher_sort(array, N, THREADS);
    std::sort(&b[0], &b[N]);
    ASSERT_EQ((int)std::equal(&array[0], &array[N], &b[0]), 1);
}

TEST(Radix_Batcher_Sort_OMP, Cannot_Sort_Negative_Elements) {
    omp_set_nested(1);
    int n = 5;
    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        array[i] = i;
    }
    ASSERT_NO_THROW(radix_batcher_sort(array, n, THREADS));
}

TEST(Radix_Batcher_Sort_OMP, Can_Sort_Zero_Elements) {
    omp_set_nested(1);
    int* array = new int[N];
    for (int i = 0; i < N; i++) {
        array[i] = 0;
    }
    radix_batcher_sort(array, N, THREADS);
    int flag = 0;
    for (int i = 0; i < N; i++) {
        if (array[i] != 0) {
            flag++;
        }
    }
    ASSERT_EQ(flag, 0);
}

TEST(Radix_Batcher_Sort_OMP, Can_Sort_Two_Times) {
    omp_set_nested(1);
    int* array = new int[N];
    gen_rnd_arr(array, N, BITS);
    radix_batcher_sort(array, N, THREADS);
    int* b = new int[N];
    duplicate_array(array, b, N);
    radix_batcher_sort(array, N, THREADS);
    ASSERT_EQ((int)std::equal(&array[0], &array[N], &b[0]), 1);
}

TEST(Radix_Batcher_Sort_OMP, Can_Odd_Even_Merge_Properly) {
    omp_set_nested(1);
    int n = 12;
    int* array = new int[n] {1, 8, 7, 2, 9, 0, 3, 1, 4, 2, 4, 1};
    int* result = new int[n / 2];
    odd_even_simple_merge(array, n, result);
    int* result1 = new int[n / 2]{ 1, 3, 4, 4, 7, 9 };
    ASSERT_EQ((int)std::equal(&result1[0], &result1[n / 2], &result[0]), 1);
}


TEST(Radix_Batcher_Sort_OMP, DISABLED_Compare_Seq_and_Omp_Average_Time) {
    omp_set_nested(1);

    std::cout << '\n' << "TESTS AMOUNT: " << TESTS << '\n';
    std::cout << '\n' << "BITS  AMOUNT: " << BITS << '\n';
    std::cout << '\n' << "ARRAY LENGTH: " << N << '\n';

    double omp_time, time1, time2 = 0;

    int* array = new int[N];

    for (int threads = THREADS; threads > 0; threads = threads >> 1) {
        omp_time = 0;
        time1 = 0;
        time2 = 0;
        std::cout << '\n' << "THREAD: " << threads << '\n';
        std::cout << '\n';

        for (int test_num = 0; test_num < TESTS; ++test_num) {
            gen_rnd_arr(array, N, BITS);
            time1 = omp_get_wtime();
            radix_batcher_sort(array, N, threads);
            time2 = omp_get_wtime() - time1;
            omp_time += time2;
        }
        std::cout << "Parallel time: " << omp_time / TESTS << " s \n";
    }

    ASSERT_NO_THROW(radix_batcher_sort(array, N, THREADS));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
