// Copyright 2020 Soboleva Julia
#ifndef MODULES_TASK_3_SOBOLEVA_J_GAUSS_FILTER_SOBOLEVA_J_GAUSS_FILTER_H_
#define MODULES_TASK_3_SOBOLEVA_J_GAUSS_FILTER_SOBOLEVA_J_GAUSS_FILTER_H_

#include <vector>
#include <cinttypes>
#include "tbb/tbb.h"

class GaussFilter {
 private:
    std::vector<uint8_t> srcVec;
    std::vector<uint8_t>* result;
    int offset, pixelHeight;
    double sigma;

 public:
    GaussFilter(std::vector<uint8_t> _srcVec, std::vector<uint8_t>* _result, int _offset, int _pixelHeight,
                double _sigma) :
        srcVec(_srcVec),
        result(_result),
        offset(_offset),
        pixelHeight(_pixelHeight),
        sigma(_sigma) {}

    void operator()(const tbb::blocked_range<int>& r) const;
};

int GetIndex(int i, int j, int offset);
std::vector<uint8_t> GetRandMatrix(int offset, int pixelHeight);
std::vector<uint8_t> Filter(std::vector<uint8_t> srcVec, int offset, int pixelHeight, double sigma = 1.0);
std::vector<uint8_t> ParFilter(std::vector<uint8_t> srcVec, int offset, int pixelHeight, int threads = 2,
                               double sigma = 1.0);

#endif  // MODULES_TASK_3_SOBOLEVA_J_GAUSS_FILTER_SOBOLEVA_J_GAUSS_FILTER_H_
