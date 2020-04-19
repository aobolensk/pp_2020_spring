// Copyright 2020 Sinitsina Maria
#include "../../../modules/task_2/sinitsina_m_simpson/simpson.h"
#include <vector>

double Simpson_Integr_OMP(double(*func)(std::vector<double>), std::vector <double> x,
        std::vector <double> y, int n, size_t dimension, std::vector<double> lim) {
  if (x.size() != y.size() || n <= 0) {
    throw "wrong data";
  }
  int N = 2 * n;
  std::vector<double> func_res(N);
  double h = (y[dimension] - x[dimension]) / N;
  double result = 0.0;
  int t = x.size();

  if (dimension == 0) {
    for (int i = 0; i < t; ++i) {
      lim.push_back(x[i]);
    }
  }

  if (x.size() == dimension + 1) {
#pragma omp parallel for firstprivate(lim)
    for (int i = 0; i < N; ++i) {
      lim[dimension] = x[dimension] + i * h;
      func_res[i] = func(lim);
    }

#pragma omp parallel for reduction(+: result)
    for (int i = 1; i < N - 1; i += 2) {
      result += 4 * func_res[i];
      result += 2 * func_res[i + 1];
    }

    result += func_res[0] + func_res[N - 1];
    result = result * h / 3.0;
    return result;
  } else {
#pragma omp parallel for firstprivate(lim)
    for (int i = 0; i < N; ++i) {
      lim[dimension] = x[dimension] + i * h;
      func_res[i] = Simpson_Integr_OMP(func, x, y, n, dimension + 1, lim);
    }
#pragma omp parallel for reduction(+: result)
    for (int i = 1; i < N - 1; i += 2) {
      result += 4 * func_res[i];
      result += 2 * func_res[i + 1];
    }

    result += func_res[0] + func_res[N - 1];
    result *= h / 3.0;
    return result;
  }
  return result;
}
