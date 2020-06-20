// Copyright 2020 Kukushkina Ksenia
#ifndef MODULES_TASK_4_KUKUSHKINA_K_SEGMENTATION_SEGMENTATION_H_
#define MODULES_TASK_4_KUKUSHKINA_K_SEGMENTATION_SEGMENTATION_H_

#include <vector>

std::vector<std::size_t> Generate_pic(std::size_t w, std::size_t h);
std::vector<std::size_t> Segmentation(const std::vector<std::size_t>& source, std::size_t w);
void Seg(std::size_t w, std::size_t start, std::size_t finish, std::vector<std::size_t>& res, std::vector<std::size_t>& tnc, std::size_t& color);
void Recolor(std::size_t start, std::size_t finish, std::vector<std::size_t>& res, std::vector<std::size_t>& tnc);

#endif  // MODULES_TASK_4_KUKUSHKINA_K_SEGMENTATION_SEGMENTATION_H_
