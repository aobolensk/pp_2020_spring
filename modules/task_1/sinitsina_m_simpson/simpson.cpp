// Copyright 2020 Sinitsina Maria
#include "../../../modules/task_1/sinitsina_m_simpson/simpson.h"
#include <vector>

double SequentialIntegr(double(*func)(std::vector<double>), std::vector <double> x,
  std::vector <double> y, const int n) {
  if (x.size() != y.size() || n <= 0) {
    throw "wrong data";
  }
  int dimension = x.size();
  std::vector<double> h(dimension);

  double odd = 0.0, even = 0.0, coff = 0.0;
  std::vector <double> part = x;

  for (int i = 0; i < dimension; i++) {
    h[i] = (y[i] - x[i]) / static_cast<double>(n);
  }

  for (int i = 1; i < n; i += 2) {
    for (int j = 0; j < dimension; j++)
      part[j] += h[j];
    odd += func(part);
    coff += 0.1;
    for (int j = 0; j < dimension; j++)
      part[j] += h[j];
    even += func(part);
    coff += 0.1;
  }
  double res = func(x) + 4 * odd + 2 * even - func(y);
  for (int i = 0; i < dimension; ++i) {
    res *= h[i];
  }
  res /= 3.0;
  return res;
}
