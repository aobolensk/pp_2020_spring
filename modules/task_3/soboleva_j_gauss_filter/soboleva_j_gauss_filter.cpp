// Copyright 2020 Soboleva Julia
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <vector>
#include <random>
#include <cinttypes>
#include "tbb/tbb.h"
#include "../../../modules/task_3/soboleva_j_gauss_filter/soboleva_j_gauss_filter.h"

int GetIndex(int i, int j, int offset) {
  return offset * i + j;
}

std::vector<uint8_t> GetRandMatrix(int offset, int pixelHeight) {
    if ((offset < 0) || (pixelHeight < 0))
        throw "Matrix size error!!!";
    std::mt19937 gen;
    gen.seed(static_cast<uint8_t>(time(0)));
    std::vector<uint8_t> a(offset * pixelHeight);
    for (int i = 0; i < offset * pixelHeight; i++) {
        a[i] = gen() % 256;
    }
    return a;
}

std::vector<uint8_t> Filter(std::vector<uint8_t> srcVec, int offset, int pixelHeight, double sigma ) {
  if ((offset < 0) || (pixelHeight < 0))
    throw "Size error!!!";
  std::vector<uint8_t> result;
  if (srcVec.size() != static_cast<size_t>(offset * pixelHeight))
    throw "Size non equal!!!";
  for (int i = 0; i < pixelHeight; i++) {
    for (int j = 0; j < offset; j++) {
      if (i == 0 || j == 0 || i == pixelHeight - 1 || j == offset - 1) {
        result.push_back(srcVec[GetIndex(i, j, offset)]);
      } else {
        double res = 0;
        for (int x = -1; x < 2; x++) {
          for (int y = -1; y < 2; y++) {
            int r = x * x + y * y;
              res += exp(-r / (2 * sigma * sigma)) * (srcVec[GetIndex(i + x, j + y, offset)]);
          }
        }
        result.push_back(static_cast<uint8_t>(res / (2 * M_PI * sigma * sigma)));
      }
    }
  }
  return result;
}

void GaussFilter::operator()(const tbb::blocked_range<int>& r) const {
    for (int j = r.begin(); j < r.end(); j++) {
        for (int i = 0; i < pixelHeight; i++) {
            if (i == 0 || j == 0 || i == pixelHeight - 1 || j == offset - 1) {
                result->operator[](GetIndex(i, j, offset)) = srcVec[GetIndex(i, j, offset)];
            } else {
                double res = 0;
                for (int x = -1; x < 2; x++) {
                    for (int y = -1; y < 2; y++) {
                        int r = x * x + y * y;
                        res += exp(-r / (2 * sigma * sigma)) * (srcVec[GetIndex(i + x, j + y, offset)]);
                    }
                }
                result->operator[](GetIndex(i, j, offset)) = static_cast<uint8_t>(res / (2 * M_PI * sigma * sigma));
            }
        }
    }
}

std::vector<uint8_t> ParFilter(std::vector<uint8_t> srcVec, int offset, int pixelHeight, int threads, double sigma) {
    if ((offset < 0) || (pixelHeight < 0))
        throw "Size error!!!";
    std::vector<uint8_t> result(offset * pixelHeight);
    if (srcVec.size() != static_cast<size_t>(offset * pixelHeight))
        throw "Size non equal!!!";
    int grainsize = 0;
    if (offset > threads) {
        grainsize = offset / threads;
    } else {
        grainsize = 1;
    }
    tbb::parallel_for(tbb::blocked_range<int>(0, offset, grainsize),
        GaussFilter(srcVec, &result, offset, pixelHeight, sigma));
    return result;
}
