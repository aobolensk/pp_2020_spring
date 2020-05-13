// Copyright 2020 Poletueva Anastasia
#ifndef MODULES_TASK_2_POLETUEVA_A_SORTING_SHELL_WITH_SIMPLE_MERGE_POLETUEVA_A_SORTING_SHELL_WITH_SIMPLE_MERGE_H_
#define MODULES_TASK_2_POLETUEVA_A_SORTING_SHELL_WITH_SIMPLE_MERGE_POLETUEVA_A_SORTING_SHELL_WITH_SIMPLE_MERGE_H_
#include <vector>
#include <utility>

std::vector<int> getRandom(int N, int seed = 0);
std::vector<int> SortShell(const std::vector<int> &a, int size);
std::vector<std::vector<int>> division(const std::vector<int>& a, unsigned int n);
std::vector<int> Merge(const std::vector<std::vector<int>>& a, int n, int size);
std::vector<int> Merge_of_two_vectors(const std::vector<int>& a, const std::vector<int>& b);
std::vector<int> Shell_with_merge(const std::vector<int>& a, int n, int size);
std::vector<int> Shell_with_merge_omp(const std::vector<int>& a, int n, int size);

#endif  // MODULES_TASK_2_POLETUEVA_A_SORTING_SHELL_WITH_SIMPLE_MERGE_POLETUEVA_A_SORTING_SHELL_WITH_SIMPLE_MERGE_H_
