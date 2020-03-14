// Copyright 2020 Parshina Sophie
#ifndef MODULES_TASK_1_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_
#define MODULES_TASK_1_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_
#include <utility>
#include <time.h>
#include <algorithm>
#include <random>

void Get_Random_Array(double* arr, int size);
int HoarePartition(double* arr, int left_index, int right_index);
void qHoareSort(double* arr, int left_index, int right_index);
int IsSorted(double* arr, int n);
#endif  // MODULES_TASK_1_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_
