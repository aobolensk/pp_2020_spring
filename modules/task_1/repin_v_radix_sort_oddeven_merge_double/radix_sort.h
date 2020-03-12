// Copyright 2020 Repin Vladimir
#ifndef MODULES_TASK_1_REPIN_V_RADIX_SORT_ODDEVEN_MERGE_DOUBLE_RADIX_SORT_H_
#define MODULES_TASK_1_REPIN_V_RADIX_SORT_ODDEVEN_MERGE_DOUBLE_RADIX_SORT_H_

#include <random>
#include <vector>
#include <ctime>
#include <cstring>

std::vector<double> GetRandomVector(int size);
void SortByByte(double *inp, double *out, int byteNum, int size);
void RadixSortDouble(double *inp, double *out, int size);
void Merge(double *inp, double *temp, int mid, int size, int even);
void OddEvenMergeSort(double *inp, double *temp, int size, int part_size);

#endif  // MODULES_TASK_1_REPIN_V_RADIX_SORT_ODDEVEN_MERGE_DOUBLE_RADIX_SORT_H_
