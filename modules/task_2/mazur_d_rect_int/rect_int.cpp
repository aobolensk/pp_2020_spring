// Copyright 2020 Mazur Daniil
#include <omp.h>
#include <vector>
#include <numeric>
#include <utility>
#include <iostream>
#include "../../../modules/task_2/mazur_d_rect_int/rect_int.h"

double rectIntSequen(const std::function<double(const std::vector<double>&)>& f,
                     std::vector <std::pair<double, double>> cord, int cuts) {
  int  blockCount = 1;
  int vSize = cord.size();
  std::vector<double> blockSize(vSize);
  for (int i = 0; i < vSize; ++i) {
    blockSize[i] = (cord[i].second - cord[i].first) / cuts;
    blockCount = blockCount * cuts;
  }
  std::vector <double> resVector(vSize);
  double intResult = 0.0;
  for (int i = 0; i < blockCount; ++i) {
    for (int j = 0; j < vSize; ++j) {
      resVector[j] = cord[j].first + (0.5 + i % cuts) * blockSize[j];
    }
    intResult += f(resVector);
  }
  for (int i = 0; i < vSize; ++i) {
    intResult *= blockSize[i];
  }
  return intResult;
}

double rectIntOmp(const std::function<double(const std::vector<double>&)>& f,
                  std::vector <std::pair<double, double>> cord, int cuts) {
  int  blockCount = 1;
  int vSize = cord.size();
  // omp_set_num_threads(5);
  std::vector<double> blockSize(vSize);
  for (int i = 0; i < vSize; ++i) {
    blockSize[i] = (cord[i].second - cord[i].first) / cuts;
    blockCount = blockCount * cuts;
  }

  double intResult = 0.0;
  #pragma omp parallel reduction(+:intResult)
  {
    std::vector <double> resVector(vSize);
    #pragma omp for
      for (int i = 0; i < blockCount; ++i) {
        for (int j = 0; j < vSize; ++j) {
          resVector[j] = cord[j].first + (0.5 + i % cuts) * blockSize[j];
        }
        intResult += f(resVector);
      }
  }
  for (int i = 0; i < vSize; ++i) {
    intResult *= blockSize[i];
  }
  return intResult;
}
