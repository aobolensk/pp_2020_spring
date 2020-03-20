// Copyright 2020 Kukushkina Ksenia

#ifndef MODULES_TASK_1_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_
#define MODULES_TASK_1_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_

#include <vector>

std::vector<int> Generate_pic(size_t w, size_t h);
std::vector<int> Segmentation(const std::vector<int> &source, size_t w);
void recolor(std::vector<int> *vec, size_t pix, int color, size_t w);
void Output(const std::vector<int>& source, size_t w);

#endif  // MODULES_TASK_1_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_
