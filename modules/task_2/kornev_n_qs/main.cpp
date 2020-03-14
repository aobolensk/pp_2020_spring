// Copyright 2020 Kornev Nikita
#include <numeric>
#include <utility>
#include <algorithm>
#include "gtest/gtest.h"
#include "../../../modules/task_2/kornev_n_qs/qs.h"

TEST(omp_qs, corr_res) {
  int n = 100000;
  double* a = new double[n], * b = new double[n];
  get_rand_arr(a, n);

  arrcpy(a, b, n);
  qs(b, 0, n - 1);
  qs_omp(a, n);

  bool res = std::equal(&a[0], &a[n], &b[0]);
  ASSERT_EQ(res, 1);
}

TEST(omp_qs, sorted_arr) {
  int n = 100000;
  double* a = new double[n], *b = new double[n];
  get_rand_arr(a, n);
  qs(a, 0, n - 1);
  arrcpy(a, b, n);
  qs_omp(b, n);

  bool res = std::equal(&a[0], &a[n], &b[0]);
  ASSERT_EQ(res, 1);
}

TEST(omp_qs, inverted_arr) {
  int n = 100000;
  double* a = new double[n], * b = new double[n];
  get_rand_arr(a, n);

  qs(a, 0, n - 1);
  arrcpy(a, b, n);

  for (int i = 0; i < n / 2; i++) {
    std::swap(a[i], a[n - i - 1]);
  }

  qs_omp(a, n);

  bool res = std::equal(&a[0], &a[n], &b[0]);
  ASSERT_EQ(res, 1);
}

TEST(omp_qs, almost_empty_arr) {
  int n = 100000;
  double* a = new double[n];
  a[0] = 1;
  qs_omp(a, n);
  ASSERT_EQ(a[n - 1], 1);
}

TEST(omp_qs, empty_arr) {
  int n = 100000;
  double* a = new double[n];

  for (int i = 0; i < n; i++) {
    a[i] = 0;
  }

  qs_omp(a, n);

  double sum = std::accumulate(&a[0], &a[n], 0);

  ASSERT_EQ(sum, 0);
}
