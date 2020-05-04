// Copyright 2020 Zinkov Artem
#include <tbb/tbb.h>
#include <random>
#include <algorithm>
#include <ctime>
#include <vector>
#include "../../../modules/task_3/zinkov_gaussian_filter_hor/gaussian_filter_hor.h"

bool operator==(const pixel& a, const pixel& b) {
    return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
}

std::vector<pixel> get_Random_Image(const std::size_t& rows, const std::size_t& cols) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned char>(time(0)));
    std::vector<pixel> image(cols * rows);
    for (auto& i : image) {
        i.r = gen();
        i.g = gen();
        i.b = gen();
    }
    return image;
}

std::vector<pixel> Gaussian_Filter_Tbb(const std::vector<pixel>& image,
    const std::size_t& rows, const std::size_t& cols) {
    int sum_mask = 16;
    std::vector<pixel> result(image.size());
    tbb::parallel_for(
        tbb::blocked_range<int>(0, rows),
        [&](const tbb::blocked_range<int>& range) {
        int r, g, b, x, y;

        for (int i = range.begin(); i != range.end(); ++i) {
            for (std::size_t j = 0; j < cols; ++j) {
                r = g = b = 0;
                for (int k = -1; k < 2; ++k) {
                    for (int p = -1; p < 2; ++p) {
                        x = i + k;
                        y = j + p;

                        if (x < 0 || x >  static_cast<int>(rows) - 1) {
                            x = i;
                        }
                        if (y < 0 || y >  static_cast<int>(cols) - 1) {
                            y = j;
                        }

                        r += static_cast<int>(image[x * cols + y].r)* GaussKernel[k + 1][p + 1];
                        g += static_cast<int>(image[x * cols + y].g)* GaussKernel[k + 1][p + 1];
                        b += static_cast<int>(image[x * cols + y].b)* GaussKernel[k + 1][p + 1];
                    }
                }
                result[i * cols + j].r = r / sum_mask;
                result[i * cols + j].g = g / sum_mask;
                result[i * cols + j].b = b / sum_mask;
            }
        }
    });
    return result;
}
