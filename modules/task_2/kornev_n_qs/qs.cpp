// Copyright 2020 Kornev Nikita
#include <omp.h>
#include <utility>
#include <vector>
#include "../../../modules/task_2/kornev_n_qs/qs.h"

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
  std::mt19937 gen(static_cast<unsigned int>(time(0)));
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

void merge(double* a, int n, double* b, int m) {
  int i = 0, j = 0, k = 0;
  double* temp = new double[n + m];
  while (i < n && j < m) {
    if (a[i] > b[j]) {
      temp[k++] = b[j++];
    } else {
      if (a[i] < b[j]) {
        temp[k++] = a[i++];
      } else {
        temp[k++] = a[i++];
        temp[k++] = b[j++];
      }
    }
  }

  while (i < n) {
    temp[k++] = a[i++];
  }

  while (j < m) {
    temp[k++] = b[j++];
  }

  for (int i = 0; i < m + n; i++) {
    a[i] = temp[i];
  }
}

void qs_omp(double* a, int n) {
  int num_threads = 2;  // define num of threads
  omp_set_num_threads(num_threads);
  std::vector<std::vector<int>> start_fin(num_threads, std::vector<int>(2));
  // [thread][0] & [thread][1] - start & finish of mini-arrays that will be sort by each thread

#pragma omp parallel  // sort
  {
    int thread = omp_get_thread_num();
    start_fin[thread][0] = thread * (n / num_threads);  // define start of mini-array that will be sort by this thread

    if (thread == num_threads - 1) {
      start_fin[thread][1] = n - 1;  // define fin
    } else {
      start_fin[thread][1] = start_fin[thread][0] + n / num_threads - 1;  // or this fin
    }

    qs(a, start_fin[thread][0], start_fin[thread][1]);
  }

  int m = num_threads / 2;  // num of pairs that will be merge by some threads
  while (start_fin.size() > 1) {
    omp_set_num_threads(m);
#pragma omp parallel
    {
      size_t thread = omp_get_thread_num();
      merge(&a[start_fin[thread * 2][0]], start_fin[thread * 2][1] - start_fin[thread * 2][0] + 1,
        &a[start_fin[thread * 2 + 1][0]], start_fin[thread * 2 + 1][1] - start_fin[thread * 2 + 1][0] + 1);
      start_fin[thread * 2][1] = start_fin[thread * 2 + 1][1];  // fin[i] = fin[i + 1]
    }
    for (int i = 1; i <= m; i++) {
      start_fin.erase(start_fin.begin() + i);  // fin[i] = fin[i + 1] then delete start_fin[i + 1]
    }
    num_threads -= m;
    m = num_threads / 2;
  }
}
