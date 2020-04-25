// Copyright 2020 Kolesova Kristina
#ifndef MODULES_TASK_2_KOLESOVA_K_SHELL_SORT_BATCH_SHELL_SORT_BATCH_H_
#define MODULES_TASK_2_KOLESOVA_K_SHELL_SORT_BATCH_SHELL_SORT_BATCH_H_

#include <vector>

std::vector<int> randVec(int size);
std::vector<int> sortShell(std::vector<int>& vec, int l, int r);
std::vector<int> oneShellBetchSort(std::vector<int>& vec);
std::vector<int> shuffle(std::vector<int>& vec, int l, int r);
std::vector<int> unshuffle(std::vector<int>& vec, int l, int r);

std::vector<int> shellBetchSort_omp(std::vector<int>& vec);

#endif // MODULES_TASK_2_KOLESOVA_K_SHELL_SORT_BATCH_SHELL_SORT_BATCH_H_
