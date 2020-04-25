// Copyright 2020 Kolesova Kristina
#ifndef MODULES_TASK_2_KOLESOVA_K_SHELL_SORT_BATCH_SHELL_SORT_BATCH_H_
#define MODULES_TASK_2_KOLESOVA_K_SHELL_SORT_BATCH_SHELL_SORT_BATCH_H_

#include <vector>

std::vector<int> randVec(int size);
std::vector<int> sortShell(const std::vector<int>& vec, int l, int r);
std::vector<int> oneShellBetchSort(const std::vector<int>& vec);
std::vector<int> shuffle(const std::vector<int>& vec, int l, int r);
std::vector<int> unshuffle(const std::vector<int>& vec, int l, int r);
std::vector<int> shellBetchSort_omp(const std::vector<int>& vec);

#endif  // MODULES_TASK_2_KOLESOVA_K_SHELL_SORT_BATCH_SHELL_SORT_BATCH_H_
