// Copyright 2020 Savkin Yuriy
#ifndef MODULES_TASK_4_SAVKIN_Y_RADIX_SORT_SIMPLE_MERGE_DOUBLE_RADIX_SORT_SIMPLE_MERGE_DOUBLE_H_
#define MODULES_TASK_4_SAVKIN_Y_RADIX_SORT_SIMPLE_MERGE_DOUBLE_RADIX_SORT_SIMPLE_MERGE_DOUBLE_H_

#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <array>
#include <limits>
#include <utility>
#include <stack>
#include <thread>
#include <mutex>
#include <functional>
#include <algorithm>

std::vector<double> getRandomVector(size_t size);
std::vector<double> getRandomVector2(size_t size);

void radixSortForDouble(double* arr, size_t count,
    size_t num_threads = std::max(std::thread::hardware_concurrency(), static_cast<unsigned>(1)));

#endif  // MODULES_TASK_4_SAVKIN_Y_RADIX_SORT_SIMPLE_MERGE_DOUBLE_RADIX_SORT_SIMPLE_MERGE_DOUBLE_H_
