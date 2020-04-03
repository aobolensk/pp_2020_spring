// Copyright 2020 Soboleva Julia
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <vector>
#include <cinttypes>
#include <random>
#include "../../../modules/task_1/soboleva_j_gauss_filter/soboleva_j_gauss_filter.h"

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
  if (srcVec == result)
    srcVec = GetRandMatrix(offset, pixelHeight);
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
