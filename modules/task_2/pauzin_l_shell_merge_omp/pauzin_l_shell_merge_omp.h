// Copyright 2020 Pauzin Leonid
#ifndef MODULES_TASK_2_PAUZIN_L_SHELL_MERGE_OMP_PAUZIN_L_SHELL_MERGE_OMP_H_
#define MODULES_TASK_2_PAUZIN_L_SHELL_MERGE_OMP_PAUZIN_L_SHELL_MERGE_OMP_H_

#include <vector>

std::vector <int> ShellSort(const std::vector <int> &vec);
std::vector<int> myMerge(std::vector<int> vec1, std::vector<int> vec2);
std::vector <int> mySortOmp(std::vector<int> vec1, std::size_t nthreads);
std::vector<int> getRandomVector(int n);

#endif  // MODULES_TASK_2_PAUZIN_L_SHELL_MERGE_OMP_PAUZIN_L_SHELL_MERGE_OMP_H_
