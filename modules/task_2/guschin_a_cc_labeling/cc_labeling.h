// Copyright 2020 Guschin Alexander
#ifndef MODULES_TASK_2_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
#define MODULES_TASK_2_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
#include <string>
#include <vector>
#include <omp.h>
#include <iostream>


std::vector<std::vector<int>> Labeling_omp(
    const std::vector<std::vector<std::int8_t>>& pic);
void Merge_omp(std::vector<std::vector<int>>* ptr, int str_row, int pr_num,
               int req_num, int end_x, int end_y);
void Print(const std::vector<std::vector<std::int32_t>>& A);

#endif  // MODULES_TASK_2_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
