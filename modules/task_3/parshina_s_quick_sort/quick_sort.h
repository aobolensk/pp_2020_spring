// Copyright 2020 Parshina Sophie
#ifndef MODULES_TASK_3_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_
#define MODULES_TASK_3_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_

#include <tbb/tbb.h>
#include <tbb/task.h>
#include <tbb/task_group.h>
#include <tbb/tick_count.h>
#include <utility>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>
#include <cmath>

void Get_Random_Array(double* arr, int size);
int HoarePartition(double* arr, int left_index, int right_index);
void qHoareSort(double* arr, int left_index, int right_index);
int IsSorted(double* arr, int n);
void Copy_elements(double*a1, double* a2, int n);
void qHoareSortTbb(double* arr, int n);
#endif   // MODULES_TASK_3_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_
