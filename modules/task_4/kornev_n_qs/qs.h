// Copyright 2020 Kornev Nikita
#ifndef MODULES_TASK_4_KORNEV_N_QS_QS_H_
#define MODULES_TASK_4_KORNEV_N_QS_QS_H_
#include <time.h>
#include <random>
#include <iostream>

void qs(double* a, int first, int last);
void get_rand_arr(double* a, int n);
void arrcpy(double* a, double* b, int n);

void merge(double* a, int n, double* b, int m);
void qs_threads(double* a, int n);
#endif  // MODULES_TASK_4_KORNEV_N_QS_QS_H_
