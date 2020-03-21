// Copyright 2020 Guschin Alexander
#ifndef MODULES_TASK_1_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
#define MODULES_TASK_1_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
#include <string>
#include <vector>

std::vector<std::vector<int>> Labeling(
    const std::vector<std::vector<std::int8_t>>& pic);
void Merge(std::vector<std::vector<int>> * ptr, int pr_num, int req_num, int end_x, int end_y);

#endif  // MODULES_TASK_1_GUSCHIN_A_CC_LABELING_CC_LABELING_H_
