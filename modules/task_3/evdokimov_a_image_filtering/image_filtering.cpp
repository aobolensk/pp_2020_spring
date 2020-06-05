// Copyright 2019 Evdokimov Artem
#include "../../../modules/task_3/evdokimov_a_image_filtering/image_filtering.h"

#include <tbb/tbb.h>
#include <time.h>

#include <algorithm>
#include <cmath>
#include <random>
#include <vector>

std::vector<int> kernel = {1, 2, 1, 2, 4, 2, 1, 2, 1};

std::vector<int> generateImage(int rows, int columns) {
  if (rows <= 0 || columns <= 0) {
    throw "Error: count of columns and rows can't be negative or equals zero.";
  }
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<int> image(rows * columns);
  for (int i = 0; i < rows * columns; i++) {
    image[i] = static_cast<unsigned int>(100 + gen() % 151);
  }
  return image;
}

std::vector<int> getTempImage(const std::vector<int>& image, int rows,
                              int columns) {
  if (rows <= 0 || columns <= 0) {
    throw "Error: count of columns and rows can't be negative or equals zero.";
  }
  auto tmpRows = rows + 2;
  auto tmpColumns = columns + 2;
  std::vector<int> tmpImage(tmpRows * tmpColumns);
  // Filling tmpImage middle by image
  for (auto rowIterator = 1; rowIterator < rows + 1; rowIterator++) {
    for (auto colIterator = 1; colIterator < columns + 1; colIterator++) {
      tmpImage[rowIterator * tmpColumns + colIterator] =
          image[(rowIterator - 1) * columns + (colIterator - 1)];
    }
  }
  // Filling tmpImage corners
  tmpImage[0] = image[0];
  tmpImage[tmpColumns - 1] = image[columns - 1];
  tmpImage[tmpRows * tmpColumns - tmpColumns] = image[rows * columns - columns];
  tmpImage[tmpRows * tmpColumns - 1] = image[rows * columns - 1];
  // Filling horizontal edges
  for (auto colIterator = 1; colIterator < columns + 1; colIterator++) {
    tmpImage[colIterator] = image[colIterator - 1];
    tmpImage[tmpRows * tmpColumns - tmpColumns + colIterator] =
        image[rows * columns - columns - 1 + colIterator];
  }
  // Filling vertical edges
  for (auto rowIterator = 1; rowIterator < rows + 1; rowIterator++) {
    tmpImage[rowIterator * tmpColumns] = image[(rowIterator - 1) * columns];
    tmpImage[(rowIterator + 1) * tmpColumns - 1] =
        image[rowIterator * columns - 1];
  }
  return tmpImage;
}

std::vector<int> imageFiltering(std::vector<int> tmpImage,
                                std::vector<int> kernel, int rows,
                                int columns) {
  if (rows <= 0 || columns <= 0) {
    throw "Error: count of columns and rows can't be negative or equals zero.";
  }
  std::vector<int> image(rows * columns);

  for (auto rowIterator = 1; rowIterator < rows + 1; rowIterator++) {
    for (auto colIterator = 1; colIterator < columns + 1; colIterator++) {
      auto result = 0, kernelIterator = 0;

      for (auto i = rowIterator - 1; i < rowIterator + 2; i++) {
        for (auto j = colIterator - 1; j < colIterator + 2; j++) {
          result += tmpImage[i * (columns + 2) + j] * kernel[kernelIterator++];
        }
      }
      image[(rowIterator - 1) * columns + (colIterator - 1)] = result / 16;
    }
  }
  return image;
}

class Filter {
 private:
  const std::vector<int>& sourceImg;
  int rows;
  int columns;
  std::vector<int>* resultImg;

 public:
  Filter(const std::vector<int>& sourceImg, int rows, int columns,
         std::vector<int>* resultImg)
      : sourceImg(sourceImg),
        rows(rows),
        columns(columns),
        resultImg(resultImg) {}

  void operator()(const tbb::blocked_range<int>& blocksCount) const {
    int rowDelta = rows / blocksCount.end();
    int colDelta = columns / blocksCount.end();
    for (int rowBlock = blocksCount.begin(); rowBlock < blocksCount.end(); rowBlock++) {
      for (int colBlock = blocksCount.begin(); colBlock < blocksCount.end(); colBlock++) {
        int rowStart = rowBlock * rowDelta + 1;
        int colStart = colBlock * colDelta + 1;

        for (int rowIterator = rowStart; rowIterator < rowStart + rowDelta;
             rowIterator++) {
          for (int colIterator = colStart; colIterator < colStart + colDelta;
               colIterator++) {
            int result = 0, cernelIterator = 0;

            for (int kernelX = rowIterator - 1; kernelX < rowIterator + 2;
                 kernelX++) {
              for (int kernelY = colIterator - 1; kernelY < colIterator + 2;
                   kernelY++) {
                result += sourceImg[kernelX * (columns + 2) + kernelY] *
                          kernel[cernelIterator++];
              }
            }
            (*resultImg)[(rowIterator - 1) * columns + (colIterator - 1)] =
                result / 16;
          }
        }
      }
    }
  }
};

std::vector<int> imageFilteringTBB(const std::vector<int>& sourceImage,
                                   int rows, int columns) {
  std::vector<int> resultImg(rows * columns);

  Filter imageObject(sourceImage, rows, columns, &resultImg);
  int streamsCount = 2;
  tbb::parallel_for(tbb::blocked_range<int>(0, streamsCount), imageObject);
  return resultImg;
}
