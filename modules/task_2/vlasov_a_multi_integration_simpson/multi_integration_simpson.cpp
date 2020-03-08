// Copyright 2020 Vlasov Andrey
#include <vector>
#include "../../../modules/task_2/vlasov_a_multi_integration_simpson/multi_integration_simpson.h"

double getIntegralSimpsonOpenMP(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n) {
  if (n <= 0)
    throw "n is negative";
  if (a.size() != b.size())
    throw "integration limits are not equal";
  int multiplicity = static_cast<int> (a.size());
  double sum = 0;
  # pragma omp parallel reduction(+: sum)
  {
    int count_thread = omp_get_num_threads();
    int id_thread = omp_get_thread_num();
    int local_n = n / count_thread;
    std::vector<double> h(multiplicity);
    for (int i = 0; i < multiplicity; i++) {
      h[i] = (b[i] - a[i]) / count_thread;
    }
    std::vector<double> local_a = a;
    for (int i = 0; i < multiplicity; i++) {
      local_a[i] += h[i] * id_thread;
    }
    std::vector<double> local_b = local_a;
    for (int i = 0; i < multiplicity; i++) {
      local_b[i] += h[i];
    }
    sum = getSum(f, local_a, local_b, local_n);
  }
  for (int i = 0; i < multiplicity; i++) {
    sum *= b[i] - a[i];
  }
  sum /= 3.0 * n;
  return sum;
}

double getSum(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n) {
  if (n <= 0)
    throw "n is negative";
  if (a.size() != b.size())
    throw "integration limits are not equal";
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
  double res = f(a) + 4 * s1 + 2 * s2 - f(b);
  return res;
}
