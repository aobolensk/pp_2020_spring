// Copyright 2020 Mazur Daniil
#include <vector>
#include <numeric>
#include <utility>
#include "../../../modules/task_1/mazur_d_rect_int/rect_int.h"

double rectIntSequen(double (*f)(std::vector<double>), std::vector <std::pair<double, double>> cord, int cuts) {
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
