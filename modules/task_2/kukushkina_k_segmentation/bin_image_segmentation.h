// Copyright 2020 Kukushkina Ksenia

#ifndef MODULES_TASK_2_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_
#define MODULES_TASK_2_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_

#include <vector>

std::vector<int> Generate_pic(std::size_t w, std::size_t h);
std::vector<int> Segmentation(const std::vector<int> &source, std::size_t w);
void Output(const std::vector<int>& source, std::size_t w);

#endif  // MODULES_TASK_2_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_
