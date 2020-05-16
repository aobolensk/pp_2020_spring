// Copyright 2020 Vlasov Andrey
#include <vector>
#include <thread>
#include "../../../modules/task_4/vlasov_a_multi_integration_simpson/multi_integration_simpson.h"

double getIntegralSimpsonThread(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n_, int num_threads) {
  if (n_ <= 0)
    throw "n is negative";
  if (a.size() != b.size())
    throw "integration limits are not equal";
  int n = 2 * n_;
  int multiplicity = static_cast<int> (a.size());
  double global_sum = 0;
  int local_n = n / num_threads;
  std::vector<double> h(multiplicity);
  for (int i = 0; i < multiplicity; i++) {
    h[i] = (b[i] - a[i]) / n;
  }
  std::vector<double> sum(num_threads + 1);
  std::thread* threads = new std::thread[num_threads];
  for (int i = 0; i < num_threads; i++) {
    threads[i] = std::thread([local_n, h, a, b, multiplicity, f, i, &sum, num_threads]() {
      std::vector<double> local_a = a;
      for (int j = 0; j < multiplicity; j++) {
        local_a[j] += h[j] * i * local_n;
      }
      std::vector<double> local_b = local_a;
      for (int j = 0; j < multiplicity; j++) {
        local_b[j] += h[j] * local_n;
      }
      if (i != num_threads - 1) {
        if ((local_n * i) % 2 == 0) {
          sum[i] = getSum(f, local_a, local_b, local_n);
        } else {
          sum[i] = getSum_odd(f, local_a, local_b, local_n);
        }
      } else {
        if ((local_n * i) % 2 == 0) {
          sum[i] = getSum(f, local_a, b, local_n);
        }
        else {
          sum[i] = getSum_odd(f, local_a, b, local_n);
        }
      }
    });
  }
  for (int i = 0; i < num_threads; ++i) {
    threads[i].join();
  }
  delete[] threads;
  for (int i = 0; i < num_threads + 1; i++) {
    global_sum += sum[i];
  }
  global_sum += f(a) - f(b);
  for (int i = 0; i < multiplicity; i++) {
    global_sum *= b[i] - a[i];
  }
  global_sum /= 3.0 * n;
  return global_sum;
}

double getSum(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n) {
  int multiplicity = static_cast<int> (a.size());
  std::vector<double> h(multiplicity);
  for (int i = 0; i < multiplicity; i++) {
    h[i] = (b[i] - a[i]) / n;
  }
  double s1 = 0.0, s2 = 0.0;
  std::vector <double> part = a;
  for (int i = 1; i < n; i += 2) {
    for (int j = 0; j < multiplicity; j++)
      part[j] += h[j];
    s1 += f(part);
    for (int j = 0; j < multiplicity; j++)
      part[j] += h[j];
    s2 += f(part);
  }
  return 4 * s1 + 2 * s2;
}

double getSum_odd(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n) {
  int multiplicity = static_cast<int> (a.size());
  std::vector<double> h(multiplicity);
  for (int i = 0; i < multiplicity; i++) {
    h[i] = (b[i] - a[i]) / n;
  }
  double s1 = 0.0, s2 = 0.0;
  std::vector <double> part = a;
  for (int i = 0; i < n; i += 2) {
    s1 += f(part);
    for (int j = 0; j < multiplicity; j++)
      part[j] += h[j];
    s2 += f(part);
    for (int j = 0; j < multiplicity; j++)
      part[j] += h[j];
  }
  return 4 * s1 + 2 * s2;
}
