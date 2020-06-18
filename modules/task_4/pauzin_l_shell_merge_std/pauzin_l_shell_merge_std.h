// Copyright 2020 Pauzin Leonid
#ifndef MODULES_TASK_4_PAUZIN_L_SHELL_MERGE_STD_PAUZIN_L_SHELL_MERGE_STD_H_
#define MODULES_TASK_4_PAUZIN_L_SHELL_MERGE_STD_PAUZIN_L_SHELL_MERGE_STD_H_

#include <vector>

std::vector <int> ShellSort(const std::vector <int> &vec);
std::vector<int> myMerge(std::vector<int> vec1, std::vector<int> vec2);
std::vector<std::vector<int>> splitVector(const std::vector<int>& vec, std::size_t nthreads);
std::vector <int> mySortSTD(std::vector<int> vec, std::size_t nthreads);
std::vector<int> getRandomVector(int n);

#endif  // MODULES_TASK_4_PAUZIN_L_SHELL_MERGE_STD_PAUZIN_L_SHELL_MERGE_STD_H_
