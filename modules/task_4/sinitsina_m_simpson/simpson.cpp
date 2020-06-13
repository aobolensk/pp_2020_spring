// Copyright 2020 Sinitsina Maria
#include "../../../modules/task_4/sinitsina_m_simpson/simpson.h"
#include <vector>
#include <thread>
#include <mutex>

void calc_func_res(double(*func)(std::vector<double>), std::vector <double> x,
  size_t dimension, double h, std::vector<double>& func_res, int N, int start, int step) {
  int end = start + step;
  double buf;
  int t = x.size();
  std::vector <double>lim(t);
  for (int i = start; i < end; ++i) {
    lim[dimension] = x[dimension] + i * h;
    buf = func(lim);    
    func_res[i] = buf;
  }
}

double Simpson_Integr_std(double(*func)(std::vector<double>), std::vector <double> x,
  std::vector <double> y, int n, size_t dimension, std::vector<double> lim) {
  if (x.size() != y.size() || n <= 0) {
    throw "wrong data";
  }
  int N = 2 * n;
  std::vector<double> func_res(N);
  double h = (y[dimension] - x[dimension]) / N;
  double result = 0.0;
  int t = x.size();

  int threadNum = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;  
  int delta = N / threadNum;
  int rem = N % threadNum;
  int start;
  int step;
  if (dimension == 0) {
    for (int i = 0; i < t; ++i) {
      lim.push_back(x[i]);
    }
  }
  if (x.size() == dimension + 1) {
    for (int threadIter = 0; threadIter < threadNum - 1; ++threadIter) {
      start = delta * threadIter;
      step = delta;
      threads.push_back(std::thread(calc_func_res, func, x, dimension, h, std::ref(func_res), N, start, step));
    }
    start = delta * (threadNum - 1);
    step = delta + rem;

    threads.push_back(std::thread(calc_func_res, func, x, dimension, h, std::ref(func_res), N, start, step));
    for (int threadIter = 0; threadIter < threadNum; ++threadIter) threads[threadIter].join();
    threads.clear();

    for (int i = 1; i < N - 1; i += 2) {
      result += 4 * func_res[i];
      result += 2 * func_res[i + 1];
    }
    result += func_res[0] + func_res[N - 1];
    result = result * h / 3.0;

    return result;
  } else {
    for (int i = 0; i < N; ++i) {
      lim[dimension] = x[dimension] + i * h;
      func_res[i] = Simpson_Integr_std(func, x, y, n, dimension + 1, lim);
    }
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


double Simpson_Integr_seq(double(*func)(std::vector<double>), std::vector <double> x,
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
    for (int i = 0; i < N; ++i) {
      lim[dimension] = x[dimension] + i * h;
      func_res[i] = func(lim);
    }

    for (int i = 1; i < N - 1; i += 2) {
      result += 4 * func_res[i];
      result += 2 * func_res[i + 1];
    }

    result += func_res[0] + func_res[N - 1];
    result = result * h / 3.0;
    return result;
  }
  else {
    for (int i = 0; i < N; ++i) {
      lim[dimension] = x[dimension] + i * h;
      func_res[i] = Simpson_Integr_seq(func, x, y, n, dimension + 1, lim);
    }
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
