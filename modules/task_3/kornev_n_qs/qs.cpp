// Copyright 2020 Kornev Nikita
#include "../../../modules/task_3/kornev_n_qs/qs.h"
#include <tbb/tbb.h>
#include <utility>
#include <vector>

tbb::task* qs_task::execute() {
  int i = first, j = last;
  bool first_task = 0, sec_task = 0;
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
    first_task = 1;
  if (first < j)
    sec_task = 1;

  if (first_task && sec_task) {
    set_ref_count(3);
    qs_task& task1 = *new(allocate_child()) qs_task(a, i, last);
    qs_task& task2 = *new(allocate_child()) qs_task(a, first, j);
    tbb::task::spawn(task1);
    tbb::task::spawn_and_wait_for_all(task2);
  } else {
    if (first_task) {
      set_ref_count(2);
      qs_task& task1 = *new(allocate_child()) qs_task(a, i, last);
      tbb::task::spawn_and_wait_for_all(task1);
    }
    if (sec_task) {
      set_ref_count(2);
      qs_task& task2 = *new(allocate_child()) qs_task(a, first, j);
      tbb::task::spawn_and_wait_for_all(task2);
    }
  }

  return NULL;
}

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

void qs_tbb(double* a, int n) {
  qs_task& mytask = *new(tbb::task::allocate_root()) qs_task(a, 0, n - 1);
  tbb::task::spawn_root_and_wait(mytask);
}

