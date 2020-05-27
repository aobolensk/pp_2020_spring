// Copyright 2020 Guschin Alexander
#ifndef MODULES_TASK_4_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
#define MODULES_TASK_4_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
#include <omp.h>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>


std::vector<std::vector<int>> Labeling_std(
    const std::vector<std::vector<std::int8_t>>& pic);
void Merge_omp(std::vector<std::vector<int>>* ptr, std::int32_t str_row,
               std::int32_t pr_num, std::int32_t req_num, std::int32_t end_x,
               std::int32_t end_y);
void Print(const std::vector<std::vector<std::int32_t>>& A);
void Fill_random(std::vector<std::vector<std::int8_t>>* ptr);
bool IsLabeled(const std::vector<std::vector<std::int32_t>>& A);
void Labeling_divided(const std::vector<std::vector<std::int8_t>>& pic,
                      std::vector<std::vector<std::int32_t>>* res,
                      int32_t* counter, int32_t start, int32_t end);


#endif  // MODULES_TASK_4_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
