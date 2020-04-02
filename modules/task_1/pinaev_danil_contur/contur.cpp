// Copyright 2020 Pinaev Danil

#include <algorithm>
#include <cmath>
#include <ctime>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <string>
#include "../../modules/task_1/pinaev_danil_contur/contur.h"

static int offset = 0;

Image generateRandomImage(int rows, int cols) {
    if (rows < 1 || cols < 1)
        throw std::runtime_error("Matrix dimensions are to be positive");

    std::mt19937 gen;
    gen.seed((unsigned)time(0) + ++offset);
    std::uniform_int_distribution<int> dis(0, 255);

    Image res(rows + 2, cols + 2);

    for (int i = 1; i < rows + 1; ++i) {
        for (int j = 1; j < cols + 1; ++j) {
            if (static_cast<uint8_t>(dis(gen)) > 200)
                res.data[i * (cols + 2) + j] = 0;
        }
    }

    return res;
}

Image getContur(const Image &in) {
    Image res(in);

    int cols = in.cols,
        rows = in.rows;

    //   _________________
    //  |     |     |     |
    //  |  1  |  2  |  3  |
    //  | ___ | ___ | ___ |
    //  |  4  |     |  6  |
    //  | ___ | ___ | ___ |
    //  |  7  |  8  |  0  |
    //  |_____|_____|_____|
    //

    // First is anchor

    // 1  - (i + 0)*(cols + 2) + (j + 0)
    // 2  - (i + 0)*(cols + 2) + (j + 1)
    // 3  - (i + 0)*(cols + 2) + (j + 2)
    // 4  - (i + 1)*(cols + 2) + (j + 0)
    // 5  - main -  (i + 1)*(cols + 2) + (j + 1)
    // 6  - (i + 1)*(cols + 2) + (j + 2)
    // 7  - (i + 2)*(cols + 2) + (j + 0)
    // 8  - (i + 2)*(cols + 2) + (j + 1)
    // 9  - (i + 2)*(cols + 2) + (j + 2)

    for (int i = 0; i < rows - 2; ++i) {
        // Main pixel index is [i][j] (rows * i + j) now
        // Now wee need to check all neighboring pixels
        for (int j = 0; j < cols - 2; ++j) {
            if (in.data[(i + 1)*(cols) + (j + 1)] == 255) {
                if (in.data[(i + 0)*(cols) + (j + 0)] == 0 ||
                    in.data[(i + 0)*(cols) + (j + 1)] == 0 ||
                    in.data[(i + 0)*(cols) + (j + 2)] == 0 ||
                    in.data[(i + 1)*(cols) + (j + 0)] == 0 ||
                    in.data[(i + 1)*(cols) + (j + 2)] == 0 ||
                    in.data[(i + 2)*(cols) + (j + 0)] == 0 ||
                    in.data[(i + 2)*(cols) + (j + 1)] == 0 ||
                    in.data[(i + 2)*(cols) + (j + 2)] == 0) {
                    res.data[(i + 1)*(cols) + (j + 1)] = 127;
                }
            }
        }
    }

    return res;
}

void print(std::string mes, const Image &img) {
    int real_rows = img.rows;
    int real_cols = img.cols;

    std::cout<< mes <<std::endl;

    if (real_rows * real_cols != static_cast<int>(img.data.size())) {
        std::cout << "real_rows * real_cols: "<< real_rows * real_cols
                  << " img.data.size(): " << img.data.size()<< std::endl
                  << "that is all" << std::endl;

        throw std::runtime_error("Alarm!!");
    }


    for (int i = 0; i < real_cols; ++i) {
        for (int j = 0; j < real_rows; ++j)
            std::cout<< img.data[i * real_cols + j]<< ", ";
        std::cout << std::endl;
    }
}
