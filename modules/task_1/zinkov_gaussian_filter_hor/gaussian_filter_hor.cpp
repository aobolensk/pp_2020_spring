// Copyright 2020 Zinkov Artem
#include <random>
#include <ctime>
#include <vector>
#include "../../../modules/task_1/zinkov_gaussian_filter_hor/gaussian_filter_hor.h"

bool operator==(const pixel& a, const pixel& b) {
  return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
}

std::vector<pixel> get_Random_Image(const int& rows, const int& cols) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned char>(time(0)));
  std::vector<pixel> image(cols * rows);
  for (auto& i : image) {
    i.r = gen();
    i.g = gen();
    i.b = gen();
  }
  return image;
}

std::vector<pixel> Gaussian_Filter_seq(const std::vector<pixel>& image, const int& rows, const int& cols) {
  int x, y;
  int r, g, b;
  int sum_mask = 16;
  std::vector<pixel> result(image.size());

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      r = g = b = 0;

      for (int k = -1; k < 2; k++) {
        for (int p = -1; p < 2; p++) {
          x = i + k;
          y = j + p;

          if (x < 0 || x >  rows - 1) {
            x = i;
          }
          if (y < 0 || y >  cols - 1) {
            y = j;
          }

          r += static_cast<int>(image[x * cols + y].r)* GaussKernel[k + 1][p + 1];
          g += static_cast<int>(image[x * cols + y].g)* GaussKernel[k + 1][p + 1];
          b += static_cast<int>(image[x * cols + y].b)* GaussKernel[k + 1][p + 1];
        }
      }
      result[i * cols + j].r = r / sum_mask;
      result[i * cols + j].g = g / sum_mask;
      result[i * cols + j].b = b / sum_mask;
    }
  }

  return result;
}
