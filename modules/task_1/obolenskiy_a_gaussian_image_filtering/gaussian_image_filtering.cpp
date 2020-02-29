// Copyright 2020 Obolenskiy Arseniy
#include <algorithm>
#include <cmath>
#include <ctime>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>
#include "../../modules/task_1/obolenskiy_a_gaussian_image_filtering/gaussian_image_filtering.h"

bool operator==(const Pixel &a, const Pixel &b) {
    return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
}

static std::vector <double> generateGaussianKernel(int dim) {
    if (dim % 2 == 0) {
        throw std::runtime_error("Kernel size must be odd!");
    }
    std::vector <double> res(dim * dim);
    const double sigma = 1., s = 2 * sigma * sigma;
    const int shift = dim / 2;
    double sum = 0.;
    for (int x = -shift; x <= shift; ++x) {
        for (int y = -shift; y <= shift; ++y) {
            sum += res[(x + shift) * dim + y + shift] = (exp(-(x * x + y * y) / s)) / (acos(-1.) * s);
        }
    }
    for (int i = 0; i < dim * dim; ++i) {
        res[i] /= sum;
    }

    return res;
}

static int offset = 0;
static const int gaussianKernelSize = 3;
static const std::vector <double> gaussianKernel = generateGaussianKernel(gaussianKernelSize);

Image generateRandomImage(int rows, int cols) {
    std::mt19937 gen;
    gen.seed((unsigned)time(0) + ++offset);
    std::uniform_int_distribution<int> dis(0, 255);
    Image result(rows * cols);
    #pragma omp parallel for
    for (int i = 0; i < rows * cols; ++i) {
        result[i] = {static_cast<uint8_t>(dis(gen)), static_cast<uint8_t>(dis(gen)), static_cast<uint8_t>(dis(gen))};
    }
    return result;
}

Image gaussianFilter(const Image &a, int rows, int cols) {
    Image res(a);
    if (rows * cols != static_cast<int>(res.size())) {
        throw std::runtime_error("Matrix dimensions do not match");
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double r = 0, g = 0, b = 0;
            int gaussianIndex = 0;
            for (int l = -gaussianKernelSize / 2; l <= gaussianKernelSize / 2; ++l) {
                for (int k = -gaussianKernelSize / 2; k <= gaussianKernelSize / 2; ++k) {
                    int idX = std::max(0, std::min(i + l, rows - 1));
                    int idY = std::max(0, std::min(j + k, cols - 1));
                    Pixel p = a[idX * cols + idY];
                    r += gaussianKernel[gaussianIndex] * p.r;
                    g += gaussianKernel[gaussianIndex] * p.g;
                    b += gaussianKernel[gaussianIndex] * p.b;
                    ++gaussianIndex;
                }
            }
            Pixel &p = res[i * cols + j];
            p.r = std::max(0, std::min(static_cast<int>(r), 255));
            p.g = std::max(0, std::min(static_cast<int>(g), 255));
            p.b = std::max(0, std::min(static_cast<int>(b), 255));
        }
    }
    return res;
}
