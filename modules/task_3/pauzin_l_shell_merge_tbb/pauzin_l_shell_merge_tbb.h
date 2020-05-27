// Copyright 2020 Pauzin Leonid
#ifndef MODULES_TASK_3_PAUZIN_L_SHELL_MERGE_TBB_PAUZIN_L_SHELL_MERGE_TBB_H_
#define MODULES_TASK_3_PAUZIN_L_SHELL_MERGE_TBB_PAUZIN_L_SHELL_MERGE_TBB_H_

#include <vector>

std::vector <int> ShellSort(const std::vector <int> &vec, int size);
std::vector<int> myMerge(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> getRandomVector(int n);
std::vector<std::vector<int>> splitVector(const std::vector<int>& vec, std::size_t nthreads);
std::vector<int> mySortTbb(const std::vector<int>& vec, std::size_t nthreads);
#endif  // MODULES_TASK_3_PAUZIN_L_SHELL_MERGE_TBB_PAUZIN_L_SHELL_MERGE_TBB_H_
