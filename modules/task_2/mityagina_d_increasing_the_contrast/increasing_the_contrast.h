// Copyright 2020 Mityagina Daria
#ifndef MODULES_TASK_2_MITYAGINA_D_INCREASING_THE_CONTRAST_INCREASING_THE_CONTRAST_H_
#define MODULES_TASK_2_MITYAGINA_D_INCREASING_THE_CONTRAST_INCREASING_THE_CONTRAST_H_

#include <omp.h>
#include <vector>

std::vector<int> generate_im(int im_width, int im_height);
std::vector<int> contrast_increase(std::vector<int> input, int im_width, int im_height);
int minimum(std::vector<int> *grayscale_image);
int maximum(std::vector<int> *grayscale_image);
int use_formula(int value, int max_value, int min_value);

#endif  // MODULES_TASK_2_MITYAGINA_D_INCREASING_THE_CONTRAST_INCREASING_THE_CONTRAST_H_
