// Copyright 2020 Mazur Daniil
#include <tbb/tbb.h>
#include <vector>
#include <numeric>
#include <functional>
#include <utility>
#include <iostream>
#include "../../../modules/task_3/mazur_d_rect_int/rect_int.h"

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

double rectIntTbb(const std::function<double(const std::vector<double>&)>& f,
                  std::vector <std::pair<double, double>> cord, int cuts) {
  int  blockCount = 1;
  int vSize = cord.size();
  std::vector<double> blockSize(vSize);
  for (int i = 0; i < vSize; ++i) {
    blockSize[i] = (cord[i].second - cord[i].first) / cuts;
    blockCount = blockCount * cuts;
  }
  std::vector <double> resVector(vSize);
  // double intResult = 0.0;
  double intResult = tbb::parallel_reduce(
  tbb::blocked_range<int>(0, blockCount), 0.f, [&](const tbb::blocked_range<int> r, double threadresult) -> double {
    for (int i = r.begin(); i != r.end(); ++i) {
      std::vector <double> resVector(vSize);
      for (int j = 0; j < vSize; j++)
        resVector[j] = cord[j].first + (0.5 + i % cuts) * blockSize[j];
      threadresult += f(resVector);
    }
    return threadresult;
  },
  std::plus<double>() );
  for (int i = 0; i < vSize; ++i) {
    intResult *= blockSize[i];
  }
  return intResult;
}

