// Copyright 2020 Utkin Konstantin
#ifndef MODULES_TASK_1_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_
#define MODULES_TASK_1_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_

#include <vector>

std::vector<std::vector<int>> getRandomPic(int col, int row);

std::vector<std::vector<int>> addBorders(const std::vector<std::vector<int>>& pic, int col, int row);
std::vector<std::vector<int>> gaussFilter(const std::vector<std::vector<int>>& pic, int col, int row);

#endif  // MODULES_TASK_1_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_
