// Copyright 2020 Kornev Nikita
#include <utility>
#include "../../../modules/task_1/kornev_n_qs/qs.h"

void qs(double* a, int first, int last) {
  int i = first, j = last;
  double pivot = a[(first + last) / 2];

  do {
    while (a[i] < pivot)
      i++;
    while (a[j] > pivot)
      j--;
    if (i <= j) {
      if (i < j) {
        std::swap(a[i], a[j]);
      }
      i++;
      j--;
    }
  } while (i <= j);

  if (i < last)
    qs(a, i, last);
  if (first < j)
    qs(a, first, j);
}

void get_rand_arr(double* a, int n) {
  std::mt19937 gen(time(0));
  std::uniform_int_distribution<> uid(0, n);
  for (int i = 0; i < n; i++) {
    a[i] = uid(gen);
  }
}

void arrcpy(double* a, double* b, int n) {
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
  }
}
