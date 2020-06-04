// Copyright 2020 Kukushkina Ksenia

#ifndef MODULES_TASK_2_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_
#define MODULES_TASK_2_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_

#include <vector>

std::vector<std::size_t> Generate_pic(std::size_t w, std::size_t h);
std::vector<std::size_t> Segmentation(const std::vector<std::size_t> &source, std::size_t w);
void Output(const std::vector<std::size_t>& source, std::size_t w);

#endif  // MODULES_TASK_2_KUKUSHKINA_K_SEGMENTATION_BIN_IMAGE_SEGMENTATION_H_
