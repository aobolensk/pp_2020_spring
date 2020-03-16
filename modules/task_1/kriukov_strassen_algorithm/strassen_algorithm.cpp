#include "strassen_algorithm.h"
#include <random>
#include <ctime>

std::vector<double> getRandomMatrix(int sz) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<double> vec(sz);
  for (int i = 0; i < sz; i++) {
    vec[i] = gen() % 99 + 1;
  }
  return vec;
}

std::vector<double> regularMultiplication(std::vector<double>& a, std::vector<double>& b)
{
  int n = static_cast<int>(sqrt(a.size()));
  std::vector<double> res(a.size());
  for(int i = 0; i < n; i++)
    for (int j = 0; j < n; j++){
      for (int k = 0; k < n; k++)
        res[j + i * n] += a[i * n + k] * b[j + k * n];
    }
  return res;
}

std::vector<double> regularSum(std::vector<double>& a, std::vector<double>& b, int sz)
{
  std::vector<double> res(sz);
  for (int i = 0; i < sz; i++) {
    res[i] = a[i] + b[i];
  }
  return res;
}

void splitMatrix(std::vector<double> &mtx, std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, std::vector<double> &d, int size) {
  unsigned int sz = static_cast<unsigned int>(sqrt(size/4));
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * 2 * sz; j < i * 2 * sz + sz; j++)
      a.push_back(mtx[j]);
    for (unsigned int j = i * 2 * sz + sz; j < i * 2 * sz + 2 * sz; j++)
      b.push_back(mtx[j]);
  }
  for (unsigned int i = sz; i < 2*sz; i++) {
    for (unsigned int j = i * 2 * sz; j < i * 2 * sz + sz; j++)
      c.push_back(mtx[j]);
    for (unsigned int j = i * 2 * sz + sz; j < i * 2 * sz + 2 * sz; j++)
      d.push_back(mtx[j]);
  }
}

void mergeMatrix(std::vector<double> &mtx, std::vector<double> &a, std::vector<double> &b, std::vector<double> &c, std::vector<double> &d, int size) {
  unsigned int sz = static_cast<unsigned int>(sqrt(size / 4));
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx.push_back(a[j]);
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx.push_back(b[j]);
  }
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx.push_back(c[j]);
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx.push_back(d[j]);
  }
}

std::vector<double> toPowerOfTwoSize(std::vector<double> &mtx) {
  unsigned int sz = static_cast<unsigned int>(sqrt(mtx.size()));
  unsigned int power = 2;
  while (sz > power)
    power *= 2;
  std::vector<double> res;
  for (unsigned i = 0; i < sz; i++) {
    for (unsigned j = 0; j < sz; j++)
      res.push_back(mtx[j + i * sz]);
    for (unsigned j = sz; j < power; j++)
      res.push_back(0);
  }
  for (unsigned i = sz; i < power; i++) {
    for (unsigned j = 0; j < power; j++)
      res.push_back(0);
  }
  return res;
}