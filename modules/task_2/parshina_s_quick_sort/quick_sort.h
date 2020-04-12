// Copyright 2020 Parshina Sophie
#ifndef MODULES_TASK_2_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_
#define MODULES_TASK_2_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_

#include <omp.h>
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
void Simple_Fusion(double * arr, int n, int m);
std::vector<int> Get_Ends(int thread_num, int n, int threads_value);
//void dump_thread(vector<vector<int>> x);
//void dump_ends(vector<vector<int>> x, int l);
//double t();
void Parallel_Division_Sort(double * arr, int n, int threads_value = 2);
#endif  // MODULES_TASK_2_PARSHINA_S_QUICK_SORT_QUICK_SORT_H_ 

