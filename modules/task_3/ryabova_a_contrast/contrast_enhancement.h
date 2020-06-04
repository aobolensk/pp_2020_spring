// Copyright 2020 Ryabova Alyona

#ifndef MODULES_TASK_3_RYABOVA_A_CONTRAST_CONTRAST_ENHANCEMENT_H_
#define MODULES_TASK_3_RYABOVA_A_CONTRAST_CONTRAST_ENHANCEMENT_H_

#include <tbb/tbb.h>
#include <cstdint>
#include <vector>

int F(int x, int xMax, int xMin);

using Image = std::vector <int>;

Image randomImage(int width, int height);
Image contrastImage(Image initImage, int width, int height);

#endif  // MODULES_TASK_3_RYABOVA_A_CONTRAST_CONTRAST_ENHANCEMENT_H_
