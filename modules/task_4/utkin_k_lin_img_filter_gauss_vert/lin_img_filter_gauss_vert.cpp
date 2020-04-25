// Copyright 2020 Utkin Konstantin
#include <thread>
#include <vector>
#include <random>
#include <ctime>
#include "../../../modules/task_4/utkin_k_lin_img_filter_gauss_vert/lin_img_filter_gauss_vert.h"

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

void threadFunction(std::vector<std::vector<int>>& in, std::vector<std::vector<int>>* out,
                    int n, int mStart, int m) {
    for (int i = mStart; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 9; ++l) {
                    (*out)[i * n + j][k] =
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

std::vector<std::vector<int>> gaussFilter(std::vector<std::vector<int>> pic, int n, int m) {
    if (n <= 0 || m <= 0) {
        throw "-1";
    }

    pic = addBorders(pic, n, m);

    std::vector<std::vector<int>> newPic(n * m, std::vector<int>(3));
    
    if (m >= NUM_THREADS) {
        std::vector<int> block(NUM_THREADS, m / NUM_THREADS);
        block[NUM_THREADS - 1] += m % NUM_THREADS;

        std::vector<std::thread> thr(NUM_THREADS);

        thr[0] = std::thread(threadFunction, std::ref(pic), &newPic, n, 0, block[0] - 1);
        for (int i = 1; i < NUM_THREADS; ++i) {
            thr[i] = std::thread(threadFunction, std::ref(pic), &newPic, n, block[i - 1], block[i - 1] - 1 + block[i]);
        }

        for (int i = 0; i < NUM_THREADS; ++i) {
            thr[i].join();
        }
    } else {
        std::thread thr(threadFunction, std::ref(pic), &newPic, n, 0, m);
    }
    return newPic;
}
