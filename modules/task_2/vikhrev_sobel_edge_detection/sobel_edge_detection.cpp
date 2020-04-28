// Copyright 2020 Vikhrev Ivan
#include <omp.h>
#include "../../../modules/task_2/vikhrev_sobel_edge_detection/sobel_edge_detection.h"

imageU sobel_par(const imageU& img) {
    imageS kernX(3, 3, { 1, 0, -1, 2, 0, -2, 1, 0, -1 });
    imageS kernY(3, 3, { 1, 2, 1, 0, 0, 0, -1, -2, -1 });
    imageU res{ img.rows, img.cols };
#pragma omp parallel for
    for (int i = 0; i < img.rows; ++i) {
       for (int j = 0; j < img.cols; ++j) {
            int id = i * img.cols + j;
            int idk = 0;
            int x{ 0 }, y{ 0 };
            for (int n = kernX.rows/(-2); n <= kernX.rows / 2; ++n) {
                for (int m = kernX.cols/(-2); m <= kernX.cols/2; ++m) {
                    int row = i + n;
                    int col = j + m;
                    if (row >= 0 && col >= 0 && row < img.rows && col < img.cols) {
                        x +=  kernX.data[idk] * img.data[row * img.cols + col];
                        y +=  kernY.data[idk] * img.data[row * img.cols + col];
                    }
                    ++idk;
                }
            }
            res.data[id] = sqrt(x*x + y * y) > 255 ? 255 : sqrt(x*x + y * y);
            x = 0;
            y = 0;
        }
    }


    return res;
}

imageU sobel_seq(const imageU& img) {
    imageS kernX(3, 3, { 1, 0, -1, 2, 0, -2, 1, 0, -1 });
    imageS kernY(3, 3, { 1, 2, 1, 0, 0, 0, -1, -2, -1 });
    int x{ 0 }, y{ 0 };
    imageU res{ img.rows, img.cols };
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            int id = i * img.cols + j;
            int idk = 0;
            for (int n = kernX.rows / (-2); n <= kernX.rows / 2; ++n) {
                for (int m = kernX.cols / (-2); m <= kernX.cols / 2; ++m) {
                    int row = i + n;
                    int col = j + m;
                    if (row >= 0 && col >= 0 && row < img.rows && col < img.cols) {
                        x += kernX.data[idk] * img.data[row * img.cols + col];
                        y += kernY.data[idk] * img.data[row * img.cols + col];
                    }
                    ++idk;
                }
            }
            res.data[id] = sqrt(x*x + y * y) > 255 ? 255 : sqrt(x*x + y * y);
            x = 0;
            y = 0;
        }
    }


    return res;
}
