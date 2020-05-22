// Copyright 2020 lesya89

#include "../../../modules/task_1/zolotareva_gauss_filter/gauss_filter.h"

Image::Image(int r, int c, bool random) {
    rows = r;
    cols = c;
    data = new unsigned char[r*c];
    if (random) {
        std::mt19937 gen;
        gen.seed(static_cast<unsigned int>(time(0)));
        std::uniform_int_distribution<> dist(0, 255);
        for (int i = 0; i < r*c; i++) { data[i] = dist(gen); }
    } else {
        memset(data, 0, r*c * sizeof(unsigned char));
    }
}

Image& Image::operator=(const Image& right) {
    if (this != &right) {
        rows = right.rows;
        cols = right.cols;
        delete[] data;
        data = new unsigned char[rows*cols];
        memcpy(data, right.data, rows*cols * sizeof(unsigned char));
    }
    return *this;
}

Image::~Image() {
    delete[] data;
}

Image::Image(int r, int c, unsigned char *d) {
    rows = r;
    cols = c;
    data = new unsigned char[r*c];
    memcpy(data, d, r*c * sizeof(unsigned char));
}

Image::Image(const Image & img) {
    rows = img.rows;
    cols = img.cols;
    data = new unsigned char[rows*cols];
    memcpy(data, img.data, rows*cols * sizeof(unsigned char));
}

bool Image::operator==(const Image & img) const {
    bool res = true;
    if (rows == img.rows && cols == img.cols) {
        for (int i = 0; i < rows*cols; i++)
            if (data[i] != img.data[i]) {
                res = false;
                break;
            }
    } else {
        res = false;
    }
    return res;
}

Image Image::GaussFilter() {
    Image result(rows, cols, false);
    double k[3][3] = { { 1 / 16.0, 2 / 16.0, 1 / 16.0 },
    { 2 / 16.0, 4 / 16.0, 2 / 16.0 },
    { 1 / 16.0, 2 / 16.0, 1 / 16.0 } };

    for (int j = 1; j < cols - 1; j++) {
        for (int i = 1; i < rows - 1; i++) {
            double x = 0;
            for (int n = -1; n < 2; n++) {
                for (int m = -1; m < 2; m++) {
                    x += k[n + 1][m + 1] * data[(i + n) * cols + (j + m)];
                }
            }
            result.data[i*cols + j] = (unsigned char)round(x);
        }
    }
    return result;
}
