// Copyright 2020 Utkin Konstantin
#include <tbb/tbb.h>
#include <vector>
#include <random>
#include <ctime>
#include "../../../modules/task_3/utkin_k_lin_img_filter_gauss_vert/lin_img_filter_gauss_vert.h"

std::vector<int> kernel = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
int divKernel = 16;

std::vector<std::vector<int>> getRandomPic(int n, int m) {
    if (n <= 0 || m <= 0) {
        throw "-1";
    }

    int size = n * m;

    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<std::vector<int>> pic(size, std::vector<int>(3));
    for (int i = 0; i < size; ++i) {
        // R:0 G:1 B:2
        for (int j = 0; j < 3; ++j) {
            // Range: [0; 255]
            pic[i][j] = gen() % 256;
        }
    }

    return pic;
}

std::vector<std::vector<int>> addBorders(std::vector<std::vector<int>> pic, int n, int m) {
    if (n <= 0 || m <= 0) {
        throw "-1";
    }

    int newN = n + 2;
    int newM = m + 2;
    std::vector<std::vector<int>> newPic(newN * newM, std::vector<int>(3));

    // Edges:
    for (int i = 0; i < 3; ++i) {
        newPic[0][i] = pic[0][i];
        newPic[newN - 1][i] = pic[n - 1][i];
        newPic[(newM - 1) * newN][i] = pic[(m - 1) * n][i];
        newPic[newN * newM - 1][i] = pic[n * m - 1][i];
    }

    // Top and bottom borders:
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            newPic[i + 1][j] = pic[i][j];
            newPic[(newM - 1) * newN + 1 + i][j] = pic[(m - 1) * n + i][j];
        }
    }

    // Right and left borders:
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
            newPic[(i + 1) * newN][j] = pic[i * n][j];
            newPic[(i + 1) * newN + newN - 1][j] = pic[i * n + n - 1][j];
        }
    }

    // Copy image:
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < 3; ++k) {
                newPic[(i + 1) * newN + 1 + j][k] = pic[i * n + j][k];
            }
        }
    }

    return newPic;
}

class gFilter {
 private:
    std::vector<std::vector<int>>& in;
    int n;
    int m;

 public:
    std::vector<std::vector<int>>& out;
    gFilter(std::vector<std::vector<int>>& in, int n, int m) : in(in), n(n), m(m), out(in) {
        if (n <= 0 || m <= 0) {
            throw "-1";
        }
        in = addBorders(in, n, m);
    }
    void operator() (const tbb::blocked_range<int>& m) const {
        for (int i = m.begin(); i != m.end(); ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < 3; ++k) {
                    for (int l = 0; l < 9; ++l) {
                        out[i * n + j][k] =
                            (in[(i + 1) * (n + 2) + (j + 1) - (n + 2 + 1)][k] * kernel[0] +
                                in[(i + 1) * (n + 2) + (j + 1) - (n + 2)][k] * kernel[1] +
                                in[(i + 1) * (n + 2) + (j + 1) - (n + 2 - 1)][k] * kernel[2] +
                                in[(i + 1) * (n + 2) + (j + 1) - 1][k] * kernel[3] +
                                in[(i + 1) * (n + 2) + (j + 1)][k] * kernel[4] +
                                in[(i + 1) * (n + 2) + (j + 1) + 1][k] * kernel[5] +
                                in[(i + 1) * (n + 2) + (j + 1) + (n + 2 - 1)][k] * kernel[6] +
                                in[(i + 1) * (n + 2) + (j + 1) + (n + 2)][k] * kernel[7] +
                                in[(i + 1) * (n + 2) + (j + 1) + (n + 2 + 1)][k] * kernel[8]) / divKernel;
                    }
                }
            }
        }
    }
};

std::vector<std::vector<int>> gaussFilter(std::vector<std::vector<int>> pic, int n, int m) {
    gFilter gf(pic, n, m);
    tbb::parallel_for(tbb::blocked_range<int>(0, m), gf);
    return gf.out;
}
