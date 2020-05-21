// Copyright 2020 Khruleva Anastasia
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <bitset>
#include "../../../modules/task_2/khruleva_a_radix_batcher_sort/radix_batcher_sort.h"

void gen_rnd_arr(int* arr, int size, int bits_value) {
    std::mt19937 gen(time(0));
    const int max_rand = pow(2, bits_value);
    std::uniform_int_distribution<> interval(0, max_rand);
    for (int i = 0; i < size; ++i)
        arr[i] = interval(gen) % max_rand;
}

void odd_even_simple_merge(int* arr, int size, int* result) {
    int half_size = size / 2;
    int* a = arr;
    int* b = arr + half_size;

    int a_index = 0, b_index = 0, result_index = 0;
    while ((a_index < half_size) && (b_index < half_size)) {
        if (a[a_index] < b[b_index]) {
            result[result_index] = a[a_index];
            ++result_index;
            a_index += 2;
        } else {
            result[result_index] = b[b_index];
            ++result_index;
            b_index += 2;
        }
    }

    int* remaining;
    int remaining_index, remaining_max;
    if (a_index == half_size) {
        remaining = b;
        remaining_index = b_index;
        remaining_max = half_size;
    } else {
        remaining = a;
        remaining_index = a_index;
        remaining_max = half_size;
    }

    for (; remaining_index < remaining_max; ++result_index, remaining_index += 2)
        result[result_index] = remaining[remaining_index];
}

void compare_exchange(int* a, int* b) {
    if (*a > * b) {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

void odd_even_merger(int* arr, int size) {
    int half_size = size >> 1;
    int* left_arr = new int[half_size];
    int* right_arr = new int[half_size];

#pragma omp parallel num_threads(2)
    {
#pragma omp single nowait
        {
            odd_even_simple_merge(arr, size, left_arr);
        }

#pragma omp single nowait
        {
            odd_even_simple_merge(arr + 1, size, right_arr);
        }

#pragma omp barrier
    }

#pragma omp parallel for
    for (int i = 0; i < half_size; ++i) {
        if (left_arr[i] < right_arr[i]) {
            arr[2 * i] = left_arr[i];
            arr[2 * i + 1] = right_arr[i];
        } else {
            arr[2 * i] = right_arr[i];
            arr[2 * i + 1] = left_arr[i];
        }
    }


#pragma omp parallel for
    for (int i = 0; i < size - 1; ++i)
        compare_exchange(arr + i, arr + i + 1);

    delete[] left_arr;
    delete[] right_arr;
}

void least_significant_digit_sort(int* arr, int size, int bits) {
    int** numbers = new int* [2];
    numbers[0] = new int[size];
    numbers[1] = new int[size];
    int counters[] = { 0, 0 };
    for (int bit_num = 0; bit_num < bits; ++bit_num) {
        for (int i = 0; i < size; ++i) {
            int bit = ((arr[i] >> bit_num) & 1);
            numbers[bit][counters[bit]] = arr[i];
            ++counters[bit];
        }
        int k = 0;
        for (int i = 0; i < counters[0]; ++i, ++k)
            arr[k] = numbers[0][i];
        for (int i = 0; i < counters[1]; ++i, ++k)
            arr[k] = numbers[1][i];
         counters[0] = counters[1] = 0;
    }

    delete[] numbers[0];
    delete[] numbers[1];
    delete[] numbers;
}

void duplicate_array(int* a, int* b, int n) {
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
}

void radix_batcher_sort(int* arr, int size, int threads_value) {
    int length = size / threads_value;

#pragma omp parallel num_threads(threads_value)
    {
        int number = omp_get_thread_num();
        least_significant_digit_sort(arr + number * length, length);
    }

    threads_value = threads_value >> 1;

    while (threads_value > 0) {
#pragma omp parallel num_threads(threads_value)
        {
            int number = omp_get_thread_num();
            odd_even_merger(arr + 2 * length * number, length * 2);
#pragma omp barrier
        }
        threads_value = threads_value >> 1;
        length = length << 1;
    }
}
