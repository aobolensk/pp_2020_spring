// Copyright 2020 Parshina Sophie
#ifndef MODULES_TASK_4_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_
#define MODULES_TASK_4_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_

#include <thread>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include <cmath>

void Get_Random_Array(double* arr, int size);
void qHoareSort(double* arr, int first, int last);
void Move_Array_To_Dest(double* first, double* last, double* res);
void Merge(double* arr1_begin, double* arr1_end, double* arr2_begin, double* arr2_end, double* dest);
void qHoareSortThreads(double* a, int n, int threads_count);
void Copy_elements(double*a1, double* a2, int n);
int IsSorted(double* arr, int n);

#endif   // MODULES_TASK_4_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_
