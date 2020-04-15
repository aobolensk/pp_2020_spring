// Copyright 2020 Kornev Nikita
#ifndef MODULES_TASK_3_KORNEV_N_QS_QS_H_
#define MODULES_TASK_3_KORNEV_N_QS_QS_H_
#include <time.h>
#include <tbb/tbb.h>
#include <random>

class qs_task : public tbb::task {
  double* a;
  int first;
  int last;

 public:
  qs_task(double* _a, int _first, int _last) : a(_a), first(_first), last(_last) {}
  task* execute();
};

void qs_tbb(double* a, int n);
void qs(double* a, int first, int last);
void get_rand_arr(double* a, int n);
void arrcpy(double* a, double* b, int n);

#endif  // MODULES_TASK_3_KORNEV_N_QS_QS_H_
