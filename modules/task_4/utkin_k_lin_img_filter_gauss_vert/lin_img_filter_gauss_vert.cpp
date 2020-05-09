// Copyright 2020 Utkin Konstantin
#include <thread>
#include <vector>
#include <random>
#include <ctime>
#include "../../../modules/task_4/utkin_k_lin_img_filter_gauss_vert/lin_img_filter_gauss_vert.h"

std::vector<int> kernel = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
int divKernel = 16;

std::vector<std::vector<int>> getRandomPic(int col, int row) {
    if (col <= 0 || row <= 0) {
        throw "-1";
    }

    int size = col * row;

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

void threadFunction(const std::vector<std::vector<int>>& in, std::vector<std::vector<int>>* out,
                    int col, int col1, int col2, int row) {
    for (int i = col1; i < col2; ++i) {
        for (int j = 0; j < row; ++j) {
            for (int k = 0; k < 3; ++k) {
                (*out)[j * col + i][k] =
                    (in[(j + 1) * (col + 2) + (i + 1) - col - 1][k] * kernel[0] +
                     in[(j + 1) * (col + 2) + (i + 1) - col][k] * kernel[1] +
                     in[(j + 1) * (col + 2) + (i + 1) - col + 1][k] * kernel[2] +
                     in[(j + 1) * (col + 2) + (i + 1) - 1][k] * kernel[3] +
                     in[(j + 1) * (col + 2) + (i + 1)][k] * kernel[4] +
                     in[(j + 1) * (col + 2) + (i + 1) + 1][k] * kernel[5] +
                     in[(j + 1) * (col + 2) + (i + 1) + col - 1][k] * kernel[6] +
                     in[(j + 1) * (col + 2) + (i + 1) + col][k] * kernel[7] +
                     in[(j + 1) * (col + 2) + (i + 1) + col + 1][k] * kernel[8]) / divKernel;
            }
        }
    }
}

std::vector<std::vector<int>> addBorders(const std::vector<std::vector<int>>& pic, int col, int row) {
    if (col <= 0 || row <= 0) {
        throw "-1";
    }

    int newCol = col + 2;
    int newRow = row + 2;
    std::vector<std::vector<int>> newPic(newCol * newRow, std::vector<int>(3));

    // Edges:
    for (int i = 0; i < 3; ++i) {
        newPic[0][i] = pic[0][i];
        newPic[newCol - 1][i] = pic[col - 1][i];
        newPic[(newRow - 1) * newCol][i] = pic[(row - 1) * col][i];
        newPic[newCol * newRow - 1][i] = pic[col * row - 1][i];
    }

    // Top and bottom borders:
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < 3; ++j) {
            newPic[i + 1][j] = pic[i][j];
            newPic[(newRow - 1) * newCol + 1 + i][j] = pic[(row - 1) * col + i][j];
        }
    }

    // Right and left borders:
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < 3; ++j) {
            newPic[(i + 1) * newCol][j] = pic[i * col][j];
            newPic[(i + 1) * newCol + newCol - 1][j] = pic[i * col + col - 1][j];
        }
    }

    // Copy image:
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            for (int k = 0; k < 3; ++k) {
                newPic[(i + 1) * newCol + 1 + j][k] = pic[i * col + j][k];
            }
        }
    }

    return newPic;
}

std::vector<std::vector<int>> gaussFilter(const std::vector<std::vector<int>>& pic, int col, int row) {
    if (col <= 0 || row <= 0) {
        throw "-1";
    }

    std::vector<std::vector<int>> in(addBorders(pic, col, row));
    std::vector<std::vector<int>> out(col * row, std::vector<int>(3));
    
    if (col >= NUM_THREADS) {
        std::vector<int> block(NUM_THREADS, col / NUM_THREADS);
        block[NUM_THREADS - 1] += col % NUM_THREADS;

        std::vector<std::thread> thr(NUM_THREADS);

        int step = 0;

        for (int i = 0; i < NUM_THREADS; ++i) {
            thr[i] = std::thread(threadFunction, std::cref(in), &out, col, step, step + block[i], row);
            step += block[i];
        }

        for (int i = 0; i < NUM_THREADS; ++i) {
            thr[i].join();
        }
    } else {
        std::thread thr(threadFunction, std::cref(in), &out, col, 0, col, row);
        thr.join();
    }

    return out;
}
