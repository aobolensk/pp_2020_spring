// Copyright 2020 Mityagina Daria
#include "../../../modules/task_3/mityagina_d_increasing_the_contrast/increasing_the_contrast.h"
#include <tbb/tbb.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <random>

class contrast_increase_tbb {
 private:
     const std::vector<int> &gr_sc_image;
     std::vector<int> *nice_contrast_image;
     int min_val;
     int max_val;
     int height;
     int width;

 public:
     contrast_increase_tbb(const std::vector<int> &src, std::vector<int> *res, int min, int max, int w, int h) :
     gr_sc_image(src),
     nice_contrast_image(res) {
        min_val = min;
        max_val = max;
        width = w;
        height = h;
     }

     void operator() (const tbb::blocked_range<int> &range) const {
        float a = (-1) * (static_cast<float>(255) / (max_val - min_val)) * min_val;
        float b = static_cast<float>(255) / (max_val - min_val);

        for (int i = range.begin(); i != range.end(); i++) {
          for (int j = 0; j < width; j++) {
            if (max_val == min_val)
              (*nice_contrast_image)[i * width + j] = 0;
            else
              (*nice_contrast_image)[i * width + j] = (a + b * gr_sc_image[i * width + j]);
          }
        }
    }
};

int minimum(std::vector<int> *grayscale_image) {
  return *std::min_element(grayscale_image->begin(), grayscale_image->end());
}

int maximum(std::vector<int> *grayscale_image) {
  return *std::max_element(grayscale_image->begin(), grayscale_image->end());
}

std::vector <int> generate_im(int width_im, int height_im) {
  std::mt19937 gen;
  int size = width_im * height_im;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector <int> grayscale_image(size);
  for (int i = 0; i < size; ++i) {
    grayscale_image[i] = gen() % 255;
  }
  return grayscale_image;
}

int use_formula(int value, int max_value, int min_value) {
  // The conversion of brightness levels is carried out according to the formula:
  // g[i] = a + b * f[i]
  // where f[i] is the old brightness value of the i-th pixel, g[i] is the new
  // value, a, b are the coefficients.
  // We choose a and b so that g[min] = 0, g[max] = 255
  if (max_value < min_value)
    throw -1;

  float a = (-1) * (static_cast<float>(255) / (max_value - min_value)) * min_value;
  float b = static_cast<float>(255) / (max_value - min_value);

  if (max_value == min_value)
    return 0;
  else
    return (a + b * value);
}

std::vector <int> contrast_increase_sequential(std::vector<int> grayscale_image, int width, int height) {
  int size = width * height, error = 0;

  if (size <= 0) {
    error = 1;
  }
  switch (error) {
    case 1:
      throw std::runtime_error("size <= 0");
  }
  std::vector<int> output(grayscale_image);
  int min = *std::min_element(grayscale_image.begin(), grayscale_image.end());
  int max = *std::max_element(grayscale_image.begin(), grayscale_image.end());

  if (max < min)
    throw -1;

  for (int i = 0; i < size; i++) {
    output[i] = use_formula(grayscale_image[i], max, min);
  }
  return output;
}

std::vector <int> contrast_increase_parallel(std::vector<int> grayscale_image, int width, int height) {
  int size = grayscale_image.size(), error = 0;
  if (size <= 0) {
    error = 1;
  }
  switch (error) {
    case 1:
      throw std::runtime_error("size <= 0");
  }
  std::vector<int> output(grayscale_image);
  int min_val = *std::min_element(grayscale_image.begin(), grayscale_image.end());
  int max_val = *std::max_element(grayscale_image.begin(), grayscale_image.end());

  if (max_val < min_val)
    throw -1;

  contrast_increase_tbb body(grayscale_image, &output, min_val, max_val, width, height);
  tbb::parallel_for(tbb::blocked_range<int>(0, height), body);

  return output;
}
