// Copyright 2020 Utkin Konstantin
#ifndef MODULES_TASK_1_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_
#define MODULES_TASK_1_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_

#include <vector>

std::vector<int> kernel = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
int divKernel = 16;

std::vector<std::vector<int>> getRandomPic(int n, int m);

std::vector<std::vector<int>> addBorders(std::vector<std::vector<int>> pic, int n, int m);
std::vector<std::vector<int>> gaussFilter(std::vector<std::vector<int>> pic, int n, int m);

#endif  // MODULES_TASK_1_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_
