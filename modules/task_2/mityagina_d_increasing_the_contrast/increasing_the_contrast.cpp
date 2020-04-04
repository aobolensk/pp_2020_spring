// Copyright 2020 Mityagina Daria
#include <omp.h>
#include "../../../modules/task_2/mityagina_d_increasing_the_contrast/increasing_the_contrast.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <ctime>
#include <random>

#define MIN(a, b)  (a < b)? a:b

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

// #pragma omp parallel for
{
  for (int i = 0; i < size; ++i) {
    grayscale_image[i] = gen() % 255;
  }
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

std::vector <int> contrast_increase(std::vector<int> grayscale_image, int width, int height, int num) {
  int size = width * height, error = 0;

  if (size <= 0) {
    error = 1;
  }
  switch (error) {
    case 1:
      throw std::runtime_error("size <= 0");
  }
  std::vector<int> output(grayscale_image);
  int min = minimum(&grayscale_image);
  int max = maximum(&grayscale_image);
  int step = 0, current = 0, start = 0, i = 0;

  if (max < min)
    throw -1;

  if (max != 255 && min != 0)
  {
    // #pragma omp parallel// num_threads(num)
#pragma omp parallel private(i, current, step, start) shared(output, grayscale_image, min, max) num_threads(num)
    {
      omp_set_num_threads(num);
      current = omp_get_thread_num();
      start = current * step;
      step = MIN(size / num, size - current * (size / num));

      #pragma omp for
      {
          for (i = start; i < start + step; i++) {
            float a = (-1) * (static_cast<float>(255) / (max - min)) * min;
            float b = static_cast<float>(255) / (max - min);
            if (max == min)
              output[i] =  0;
            else
              output[i] = (a + b * grayscale_image[i]);
          }
      }
    }
    return output;
  }
  else
  {
    return grayscale_image;
  }
}
