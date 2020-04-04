// Copyright 2020 Konnov Sergey

#ifndef MODULES_TASK_1_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_
#define MODULES_TASK_1_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_

#include <vector>

std::vector<double> countingSort(std::vector<double> array, int byteNum);
std::vector<double> radixSortOddEvenMergeDouble(const std::vector<double>& array);
std::vector<double> getRandomVector(int size, double lower_bound, double upper_bound, int seed = -1);

#endif  // MODULES_TASK_1_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_
