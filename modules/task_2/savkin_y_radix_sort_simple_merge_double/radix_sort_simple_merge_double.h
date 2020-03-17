// Copyright 2020 Savkin Yuriy
#ifndef MODULES_TASK_2_SAVKIN_Y_RADIX_SORT_SIMPLE_MERGE_DOUBLE_RADIX_SORT_SIMPLE_MERGE_DOUBLE_H_
#define MODULES_TASK_2_SAVKIN_Y_RADIX_SORT_SIMPLE_MERGE_DOUBLE_RADIX_SORT_SIMPLE_MERGE_DOUBLE_H_

#include <omp.h>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>
#include <limits>
#include <utility>
#include <stack>

std::vector<double> getRandomVector(size_t size);
std::vector<double> getRandomVector2(size_t size);

void radixSortForDouble(double* arr, size_t count, size_t num_threads = omp_get_max_threads());

#endif  // MODULES_TASK_2_SAVKIN_Y_RADIX_SORT_SIMPLE_MERGE_DOUBLE_RADIX_SORT_SIMPLE_MERGE_DOUBLE_H_
