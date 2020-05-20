// Copyright 2020 Myshkin Andrey
#ifndef MODULES_TASK_2_MYSHKIN_A_RADIX_SORT_OMP_RADIX_SORT_DOUBLE_H_
#define MODULES_TASK_2_MYSHKIN_A_RADIX_SORT_OMP_RADIX_SORT_DOUBLE_H_
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <random>


int getRandomArray(double* buffer, int length, double rangebot, double rangetop);
int ArrayComparison(double* buffer1, double *buffer2, int length);
int MergeArraySigned(double* buffer1, int length1, double *buffer2, int length2, double *result);
int SortingCheck(double *buffer, int length);

int RadixSortUnsigned(double *buffer, int length);
int RadixSort(double* buffer, int length);

int MergeArrayForOmp(double* buffer1, int length1, double* buffer2, int length2);
int RadixSortOmp(double* buffer, int length, int num_threads);

#endif  // MODULES_TASK_2_MYSHKIN_A_RADIX_SORT_OMP_RADIX_SORT_DOUBLE_H_

