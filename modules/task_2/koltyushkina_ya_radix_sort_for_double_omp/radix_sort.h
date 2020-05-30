// Copyright 2020 Koltyushkina Yanina

#ifndef MODULES_TASK_2_KOLTYUSHKINA_YA_RADIX_SORT_FOR_DOUBLE_OMP_RADIX_SORT_H_
#define MODULES_TASK_2_KOLTYUSHKINA_YA_RADIX_SORT_FOR_DOUBLE_OMP_RADIX_SORT_H_

#include <omp.h>
#include <vector>
#include <queue>
#include <utility>
#include <iostream>

class task {
 public:
  task* ref;
  int count_depends;
  virtual void do_task() = 0;
  virtual ~task() {}
};

class sortTask : public task {
  double * mas;
  int index, len;
  std::vector<double> ans;
 public:
  sortTask(double* mas, int index, int len);
  void do_task() override;
};

class mergeTask : public task {
  double * inmas;
  int index1, len1, index2, len2;
 public:
  mergeTask(double * inmas, int index1, int len1, int index2, int len2);
  void do_task() override;
};

void get_tree_task(double* inmas, int left, int right, task* prev_task,
  const std::vector<int>& portion, task* queue[], bool is_begin = false);
double* RandMas(int len, double low = 0, double high = 100);
void RadixSortPart(double *inmas, double**outmas, int len, int byteN);
void RadixSortAll(double**inmas, int len);
void RadixSortAllParallel(double ** inmas, int len);

#endif  // MODULES_TASK_2_KOLTYUSHKINA_YA_RADIX_SORT_FOR_DOUBLE_OMP_RADIX_SORT_H_
