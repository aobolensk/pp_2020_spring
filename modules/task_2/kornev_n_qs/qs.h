// Copyright 2020 Kornev Nikita
#ifndef MODULES_TASK_2_KORNEV_N_QS_QS_H_
#define MODULES_TASK_2_KORNEV_N_QS_QS_H_
#include <time.h>
#include <random>

void qs(double* a, int first, int last);
void get_rand_arr(double* a, int n);
void arrcpy(double* a, double* b, int n);

void merge(double* a, int n, double* b, int m);
void qs_omp(double* a, int n);
#endif  // MODULES_TASK_2_KORNEV_N_QS_QS_H_
