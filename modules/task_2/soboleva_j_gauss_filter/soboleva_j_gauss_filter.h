// Copyright 2020 Soboleva Julia
#ifndef MODULES_TASK_2_SOBOLEVA_J_GAUSS_FILTER_SOBOLEVA_J_GAUSS_FILTER_H_
#define MODULES_TASK_2_SOBOLEVA_J_GAUSS_FILTER_SOBOLEVA_J_GAUSS_FILTER_H_

#include <vector>

int GetIndex(int i, int j, int offset);
std::vector<uint8_t> GetRandMatrix(int offset, int pixelHeight);
std::vector<uint8_t> Filter(std::vector<uint8_t> srcVec, int offset, int pixelHeight, double sigma = 1.0);
std::vector<uint8_t> ParFilter(std::vector<uint8_t> srcVec, int offset, int pixelHeight, int threads = 2,
                               double sigma = 1.0);

#endif  // MODULES_TASK_2_SOBOLEVA_J_GAUSS_FILTER_SOBOLEVA_J_GAUSS_FILTER_H_
