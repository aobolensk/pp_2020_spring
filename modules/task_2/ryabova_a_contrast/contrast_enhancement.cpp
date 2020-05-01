// Copyright 2020 Ryabova Alyona

#include <algorithm>
#include <cmath>
#include <ctime>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "../../modules/task_2/ryabova_a_contrast/contrast_enhancement.h"


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

    int const numThreads = 3;
    int numberThread;
    omp_set_num_threads(numThreads);

    int mins[numThreads], maxs[numThreads];
    int min = 255, max = 0;

#pragma omp parallel
    {
        numberThread = omp_get_thread_num();
        mins[numberThread] = 255;
        maxs[numberThread] = 0;
        #pragma omp for schedule (static)
        for (int i = 0; i < width * height; i++) {
            if (mins[numberThread] > initImage[i])
                mins[numberThread] = initImage[i];
            if (maxs[numberThread] < initImage[i])
                maxs[numberThread] = initImage[i];
        }
    }
    for (int i = 0; i < numThreads; i++) {
        if (mins[i] < min)
            min = mins[i];
        if (maxs[i] > max)
            max = maxs[i];
    }

    for (int i = 0; i < width * height; i++) {
        result[i] = F(initImage[i], max, min);
    }

    return result;
}
