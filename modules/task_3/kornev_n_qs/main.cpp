// Copyright 2020 Kornev Nikita
#include <numeric>
#include <utility>
#include <algorithm>
#include "gtest/gtest.h"
#include "tbb/tbb.h"
#include "../../../modules/task_3/kornev_n_qs/qs.h"

TEST(tbb_qs, corr_res) {
  int n = static_cast<int>(1e5);
  double* a = new double[n], * b = new double[n];
  get_rand_arr(a, n);
  arrcpy(a, b, n);

  qs(a, 0, n - 1);
  qs_tbb(b, n);

  bool res = std::equal(&a[0], &a[n], &b[0]);
  ASSERT_EQ(res, 1);
}

TEST(tbb_qs, sorted_arr) {
  int n = static_cast<int>(1e5);
  double* a = new double[n], * b = new double[n];
  get_rand_arr(a, n);

  qs(a, 0, n - 1);
  arrcpy(a, b, n);
  qs_tbb(b, n);

  bool res = std::equal(&a[0], &a[n], &b[0]);
  ASSERT_EQ(res, 1);
}

TEST(tbb_qs, inverted_arr) {
  int n = static_cast<int>(1e5);
  double* a = new double[n], * b = new double[n];
  get_rand_arr(a, n);

  qs(a, 0, n - 1);
  arrcpy(a, b, n);

  for (int i = 0; i < n / 2; i++) {
    std::swap(a[i], a[n - i - 1]);
  }

  qs_tbb(a, n);
  bool res = std::equal(&a[0], &a[n], &b[0]);
  ASSERT_EQ(res, 1);
}

TEST(tbb_qs, almost_empty_arr) {
  int n = static_cast<int>(1e5);
  double* a = new double[n];

  a[0] = 1;
  for (int i = 1; i < n; i++) {
    a[i] = 0;
  }

  qs_tbb(a, n);
  ASSERT_EQ(a[n - 1], 1);
}

TEST(tbb_qs, empty_arr) {
  int n = static_cast<int>(1e5);
  double* a = new double[n];

  for (int i = 0; i < n; i++) {
    a[i] = 0;
  }

  qs_tbb(a, n);

  double sum = std::accumulate(&a[0], &a[n], 0);
  ASSERT_EQ(sum, 0);
}
