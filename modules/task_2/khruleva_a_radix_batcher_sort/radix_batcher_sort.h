// Copyright 2020 Khruleva Anastasia
#ifndef MODULES_TASK_2_KHRULEVA_A_RADIX_BATCHER_SORT_RADIX_BATCHER_SORT_H_
#define MODULES_TASK_2_KHRULEVA_A_RADIX_BATCHER_SORT_RADIX_BATCHER_SORT_H_

#include <omp.h>
#include <utility>
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <bitset>

#define BITS 8

void gen_rnd_arr(int* arr, int size, int bits_value);
void odd_even_simple_merge(int* arr, int size, int* result);
void compare_exchange(int* a, int* b);
void odd_even_merger(int* arr, int size);
void least_significant_digit_sort(int* arr, int size, int bits = BITS);
void duplicate_array(int* a, int* b, int n);
void radix_batcher_sort(int* arr, int size, int threads_value);

#endif   // MODULES_TASK_2_KHRULEVA_A_RADIX_BATCHER_SORT_RADIX_BATCHER_SORT_H_
