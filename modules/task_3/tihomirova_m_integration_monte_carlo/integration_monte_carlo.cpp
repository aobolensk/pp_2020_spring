// Copyright 2020 Tihomirova Mariya
#include <vector>
#include <functional>
#include <random>
#include <ctime>
#include "../../../modules/task_3/tihomirova_m_integration_monte_carlo/integration_monte_carlo.h"

double getIntegralTBB(int n, const std::vector<double>& low, const std::vector<double>& top,
  const std::function<double(const std::vector<double>&)>& f) {
  if (low.size() != top.size())
    throw "different size integration limits";
  if (low.empty() || top.empty())
    throw "integration limits are empty";
  if (n <= 0)
    throw "number points <= 0";
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  int dimension = static_cast<int>(low.size());
  std::vector<std::uniform_real_distribution<double>> rand_(dimension);
  std::vector<double> rand_vec(dimension);
  for (int i = 0; i < dimension; i++)
    rand_[i] = std::uniform_real_distribution<double>(low[i], top[i]);

  double global_res = tbb::parallel_reduce(tbb::blocked_range<int>(0, n),
    0.f, [&](const tbb::blocked_range<int> r, double res) -> double {
    for (int i = r.begin(); i != r.end(); ++i) {
      for (int j = 0; j < dimension; j++)
        rand_vec[j] = rand_[j](gen);
      res += f(rand_vec);
    }
    return res;
  },
  std::plus<double>());

  for (int i = 0; i < dimension; i++)
    global_res *= (top[i] - low[i]);
  global_res /= n;
  return global_res;
}
