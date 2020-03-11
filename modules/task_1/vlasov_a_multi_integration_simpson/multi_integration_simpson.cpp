// Copyright 2020 Vlasov Andrey
#include <vector>
#include "../../../modules/task_1/vlasov_a_multi_integration_simpson/multi_integration_simpson.h"

double getIntegralSimpsonSequentional(double(*f)(std::vector<double>), const std::vector<double>& a,
  const std::vector<double>& b, int n) {
  if (n <= 0)
    throw "n is negative";
  if (a.size() != b.size())
    throw "integration limits are not equal";
  int multiplicity = a.size();
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
  for (int i = 0; i < multiplicity; i++) {
    res *= b[i] - a[i];
  }
  res /= 3.0 * n;
  return res;
}
