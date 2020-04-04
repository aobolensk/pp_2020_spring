// Copyright 2020 Bandenkov Daniil
#ifndef MODULES_TASK_1_BANDENKOV_D_SHELL_BATCHER_SORT_SHELL_BATCHER_H_
#define MODULES_TASK_1_BANDENKOV_D_SHELL_BATCHER_SORT_SHELL_BATCHER_H_

#include <vector>
#include <string>

std::vector<int> getRandomVector(int  sz);
std::vector<int> shellSort(const std::vector<int> &A, int size);
std::vector<int> evenBatcher(const std::vector<int>& A, const std::vector<int>& B);
std::vector<int> oddBatcher(const std::vector<int> &A, const std::vector<int> &B);
std::vector<int> mergeBatcher(const std::vector<int>& A, const std::vector<int>& B);
std::vector<int> shellBatch(const std::vector<int>& A, int size);

#endif  // MODULES_TASK_1_BANDENKOV_D_SHELL_BATCHER_SORT_SHELL_BATCHER_H_
