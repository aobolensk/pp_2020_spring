// Copyright 2020 Myshkin Andrey

#ifndef MODULES_TASK_3_MYSHKIN_A_RADIX_SORT_DOUBLE_RADIX_SORT_TBB_H_
#define MODULES_TASK_3_MYSHKIN_A_RADIX_SORT_DOUBLE_RADIX_SORT_TBB_H_
#include <time.h>
#include <stdlib.h>
#include <random>

int getRandomArray(double* buffer, int length, double rangebot, double rangetop);
int MergeArrays(double* buffer1, int length1, double *buffer2, int length2, double *result);
int SortingCheck(double *buffer, int length);

int RadixSort(double* buffer, int length, int NumThreads);

#endif  // MODULES_TASK_3_MYSHKIN_A_RADIX_SORT_DOUBLE_RADIX_SORT_TBB_H_
