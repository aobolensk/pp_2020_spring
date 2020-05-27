// Copyright 2020 Savosina Aleksandra
#include <cmath>
#include <vector>
#include "../../../modules/task_1/savosina_a_sobel/savosina_a.h"

mainImage sobel(const mainImage& _img) {
  std::vector<int> vec(_img.size);
  mainImage result{_img.height, _img.width, vec};
  int ind, index;
  int h, w;

  mask mask1;
  mask1.height = 3;
  mask1.width = 3;
  mask1.pict = {1, 0, -1, 2, 0, -2, 1, 0, -1};

  mask mask2;
  mask2.height = 3;
  mask2.width = 3;
  mask2.pict = {1, 2, 1, 0, 0, 0, -1, -2, -1};
  int x = 0;
  int y = 0;

  for (int i = 0; i < _img.height; ++i) {
    for (int j = 0; j < _img.width; ++j) {
      ind = i * _img.width + j;
      index = 0;
      for (int t = mask1.height / (-2); t <= mask1.height / 2; t++) {
        for (int k = mask1.width / (-2); k <= mask1.width / 2; k++) {
          h = i + t;
          w = j + k;
          if (h >= 0 && w >= 0 && h < _img.height && w < _img.width) {
            x += mask1.pict[index] * _img.pict[w + h * _img.width];
            y += mask2.pict[index] * _img.pict[w + h * _img.width];
          }
          index++;
        }
      }

      if (sqrt(x * x + y * y) > 255)
        result.pict[ind] = 255;
      else
        result.pict[ind] = sqrt(x * x + y * y);

      x = 0;
      y = 0;
    }
  }
  return result;
}
