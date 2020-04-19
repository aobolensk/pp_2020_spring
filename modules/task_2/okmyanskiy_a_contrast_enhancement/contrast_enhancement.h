// Copyright 2020 Okmyanskiy Andrey

#ifndef MODULES_TASK_2_OKMYANSKIY_A_CONTRAST_ENHANCEMENT_CONTRAST_ENHANCEMENT_H_
#define MODULES_TASK_2_OKMYANSKIY_A_CONTRAST_ENHANCEMENT_CONTRAST_ENHANCEMENT_H_

#include <omp.h>
#include <vector>

std::vector<int> getRandomMatrix(int width, int height);
int linearHistogramStretching(int value, int max, int min);
std::vector<int> getResultMatrixSeq(std::vector<int> initial, int width, int height);
std::vector<int> getResultMatrixOmp(std::vector<int> initial, int width, int height);

#endif  // MODULES_TASK_2_OKMYANSKIY_A_CONTRAST_ENHANCEMENT_CONTRAST_ENHANCEMENT_H_
