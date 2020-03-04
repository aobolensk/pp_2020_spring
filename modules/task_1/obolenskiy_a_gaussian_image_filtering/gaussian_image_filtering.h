// Copyright 2020 Obolenskiy Arseniy
#ifndef MODULES_TASK_1_OBOLENSKIY_A_GAUSSIAN_IMAGE_FILTERING_GAUSSIAN_IMAGE_FILTERING_H_
#define MODULES_TASK_1_OBOLENSKIY_A_GAUSSIAN_IMAGE_FILTERING_GAUSSIAN_IMAGE_FILTERING_H_
#include <cstdint>
#include <vector>

struct Pixel {
    uint8_t r, g, b;
    Pixel() = default;
    ~Pixel() = default;
};

bool operator==(const Pixel &a, const Pixel &b);

using Image = std::vector <Pixel>;

Image generateRandomImage(int rows, int cols);
Image gaussianFilter(const Image &a, int rows, int cols);

#endif  // MODULES_TASK_1_OBOLENSKIY_A_GAUSSIAN_IMAGE_FILTERING_GAUSSIAN_IMAGE_FILTERING_H_
