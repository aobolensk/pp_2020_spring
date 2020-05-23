// Copyright 2020 Ryabova Alyona

#include <algorithm>
#include <cmath>
#include <ctime>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "../../modules/task_3/ryabova_a_contrast/contrast_enhancement.h"

int grainSize = 5;

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
    int minimum = 255, maximum = 0;

    int const numThreads = 3;

    tbb::task_scheduler_init init(numThreads);

    size_t gs = ((initImage.size() / 1000) > 1 ? (initImage.size() / 1000) : 1);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, initImage.size(), gs),
        [&](tbb::blocked_range<size_t> r) {
            for (size_t i = r.begin(); i != r.end(); ++i) {
                if (initImage[i] > maximum) {
                    maximum = initImage[i];
                }
                if (initImage[i] < minimum) {
                    minimum = initImage[i];
                }
            }
        }, tbb::simple_partitioner());


    for (int i = 0; i < width * height; i++) {
        result[i] = F(initImage[i], maximum, minimum);
    }

    return result;
}
