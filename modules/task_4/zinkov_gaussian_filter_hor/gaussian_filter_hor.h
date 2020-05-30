// Copyright 2020 Zinkov Artem
#ifndef MODULES_TASK_4_ZINKOV_GAUSSIAN_FILTER_HOR_GAUSSIAN_FILTER_HOR_H_
#define MODULES_TASK_4_ZINKOV_GAUSSIAN_FILTER_HOR_GAUSSIAN_FILTER_HOR_H_

#include <vector>

struct pixel {
  unsigned char r, g, b;
};
bool operator==(const pixel& a, const pixel& b);

constexpr int GaussKernel[3][3]{ {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };

std::vector<pixel> get_Random_Image(const std::size_t& rows, const std::size_t& cols);
std::vector<pixel> Gaussian_Filter_Thread(const std::vector<pixel>& image,
    const std::size_t& rows, const std::size_t& cols);

#endif  // MODULES_TASK_4_ZINKOV_GAUSSIAN_FILTER_HOR_GAUSSIAN_FILTER_HOR_H_
