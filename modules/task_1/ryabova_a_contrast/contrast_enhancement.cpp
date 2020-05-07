// Copyright 2020 Ryabova Alyona

#include <algorithm>
#include <cmath>
#include <ctime>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>
#include "../../modules/task_1/ryabova_a_contrast/contrast_enhancement.h"


int F(int x, int xMax, int xMin) {
    if (xMax != xMin)
        return static_cast<int>((255 * (x - xMin)) / (xMax - xMin));
    else
        return 0;
}

static int offset = 0;

Image randomImage(int width, int height) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)) + ++offset);

    Image result(width * height);
    for (int i = 0; i < width * height; i++) {
        result[i] = gen() % 240;
    }
    return result;
}

Image contrastImage(Image initImage, int width, int height) {
    if (((width * height) > 0) && (initImage.size() != static_cast<size_t>(width * height))) {
        throw - 1;
    }
    Image result(initImage);
    int min = 255, max = 0;

    for (int i = 0; i < width * height; i++) {
        if (min > initImage[i])
            min = initImage[i];
        if (max < initImage[i])
            max = initImage[i];
    }

    for (int i = 0; i < width * height; i++) {
        result[i] = F(initImage[i], max, min);
    }

    return result;
}
