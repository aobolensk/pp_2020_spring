// Copyright 2020 Utkin Konstantin
#ifndef MODULES_TASK_4_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_
#define MODULES_TASK_4_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_

#include <vector>

constexpr auto NUM_THREADS = 6;

std::vector<std::vector<int>> getRandomPic(int n, int m);

void threadFunction(std::vector<std::vector<int>>& in, std::vector<std::vector<int>>* out,
                    int n, int mStart, int m);

void tf(std::vector<std::vector<int>>* out);

std::vector<std::vector<int>> addBorders(std::vector<std::vector<int>> pic, int n, int m);
std::vector<std::vector<int>> gaussFilter(std::vector<std::vector<int>> pic, int n, int m);

#endif  // MODULES_TASK_4_UTKIN_K_LIN_IMG_FILTER_GAUSS_VERT_LIN_IMG_FILTER_GAUSS_VERT_H_
