// Copyright 2020 Bandenkov Daniil
#ifndef MODULES_TASK_2_BANDENKOV_D_SHELL_BANCHER_SHELL_BATCHER_H_
#define MODULES_TASK_2_BANDENKOV_D_SHELL_BANCHER_SHELL_BATCHER_H_

#include <vector>
#include <utility>
#include <functional>

std::vector<int> getRandomVector(int  sz);
std::vector<int> shellSort(const std::vector<int>& A, int size);
std::vector<int> evenBatcher(const std::vector<int>& A, const std::vector<int>& B);
std::vector<int> oddBatcher(const std::vector<int>& A, const std::vector<int>& B);
std::vector<int> mergeBatcher(const std::vector<int>& A, const std::vector<int>& B);
std::vector<std::vector<int>> splitVector(const std::vector<int>& vec, size_t n);
std::vector<int> oddevenMerge_seq(const std::vector<std::vector<int>>& A, const int n, int size);
std::vector<int> oddevenMerge_omp(const std::vector<std::vector<int>>& A, const int n, int size);
std::vector<int> shellBatcher_seq(const std::vector<int>& A, const int n, int size);
std::vector<int> shellBatcher_omp(const std::vector<int>& A, const int n, int size);

#endif  // MODULES_TASK_2_BANDENKOV_D_SHELL_BANCHER_SHELL_BATCHER_H_
