// Copyright 2020 lesya89

#ifndef MODULES_TASK_1_ZOLOTAREVA_GAUSS_FILTER_GAUSS_FILTER_H_
#define MODULES_TASK_1_ZOLOTAREVA_GAUSS_FILTER_GAUSS_FILTER_H_

#include <random>
#include <iostream>
#include <ctime>
#include <cstring>

class Image {
 public:
    unsigned char *data;
    int rows;
    int cols;
    Image(int r, int c, bool random);
    Image(int r, int c, unsigned char *d);
    Image(const Image& img);
    Image& operator=(const Image& right);
    bool operator== (const Image& img) const;
    bool operator!= (const Image& img) const { return !(*this == img); }
    Image GaussFilter();
    ~Image();
};

#endif  // MODULES_TASK_1_ZOLOTAREVA_GAUSS_FILTER_GAUSS_FILTER_H_
