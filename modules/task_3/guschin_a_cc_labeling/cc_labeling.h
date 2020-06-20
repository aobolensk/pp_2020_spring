// Copyright 2020 Guschin Alexander
#ifndef MODULES_TASK_3_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
#define MODULES_TASK_3_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
#include <omp.h>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>


std::vector<std::vector<int>> Labeling_tbb(
    const std::vector<std::vector<std::int8_t>>& pic);
void Merge_tbb(std::vector<std::vector<int>>* ptr, std::int32_t str_row,
               std::int32_t pr_num, std::int32_t req_num, std::int32_t end_x,
               std::int32_t end_y);
void Print(const std::vector<std::vector<std::int32_t>>& A);
void Fill_random(std::vector<std::vector<std::int8_t>>* ptr);
bool IsLabeled(const std::vector<std::vector<std::int32_t>>& A);


#endif  // MODULES_TASK_3_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
