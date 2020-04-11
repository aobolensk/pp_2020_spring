// Copyright 2020 Okmyanskiy Andrey

#ifndef MODULES_TASK_1_OKMYANSKIY_A_CONTRAST_ENHANCEMENT_CONTRAST_ENHANCEMENT_H_
#define MODULES_TASK_1_OKMYANSKIY_A_CONTRAST_ENHANCEMENT_CONTRAST_ENHANCEMENT_H_

#include <vector>

std::vector<int> getRandomMatrix(int width, int height);
int linearHistogramStretching(int value, int max, int min);
std::vector<int> getResultMatrix(std::vector<int> initial, int width, int height);

#endif  // MODULES_TASK_1_OKMYANSKIY_A_CONTRAST_ENHANCEMENT_CONTRAST_ENHANCEMENT_H_
