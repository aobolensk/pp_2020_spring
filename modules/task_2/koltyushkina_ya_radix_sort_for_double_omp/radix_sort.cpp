// Copyright 2020 Koltyushkina Yanina

// #include "./radix_sort.h"
#include "../../../modules/task_2/koltyushkina_ya_radix_sort_for_double_omp/radix_sort.h"
#include <omp.h>
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include <utility>
#include <queue>
#include <limits>

sortTask::sortTask(double* mas, int index, int len) :
  mas(mas), index(index), len(len) {
  count_depends = 0;
}

void sortTask::do_task() {
  double * ms = mas + index;
  RadixSortAll(&ms, len);
}

mergeTask::mergeTask(double* inmas, int index1, int len1, int index2, int len2) :
  inmas(inmas), index1(index1), len1(len1), index2(index2), len2(len2) {
  count_depends = 2;
}

void mergeTask::do_task() {
  std::vector<double>tmp(len1 + len2);
  int ind1 = index1, ind2 = index2, t = 0;
  while (ind1 < len1 + index1 && ind2 < len2 + index2) {
    if (inmas[ind1] < inmas[ind2]) {
      tmp[t++] = inmas[ind1++];
    } else {
      tmp[t++] = inmas[ind2++];
    }
  }
  while (ind1 < len1 + index1)
    tmp[t++] = inmas[ind1++];
  while (ind2 < len2 + index2)
    tmp[t++] = inmas[ind2++];
  for (int i = 0; i < t; i++) {
    inmas[index1 + i] = tmp[i];
  }
}

void RadixSortPart(double *inmas, double **outmas, int len, int byteN) {
  if (len == 0)
    return;
  unsigned char *bymas = (unsigned char*)inmas;
  int schet[256];
  int smesh;
  // memset(schet, 0, sizeof(int) * 256);
  for (int i = 0; i < 256; i++) {
    schet[i] = 0;
  }

  for (int i = 0; i < len; i++) {
    schet[bymas[8 * i + byteN]]++;
  }

  int s = 0;
  for (s = 0; s < 256; s++) {
    if (schet[s] != 0)
      break;
  }

  smesh = schet[s];
  schet[s] = 0;
  s++;

  int a;
  for (; s < 256; s++) {
    a = schet[s];
    schet[s] = smesh;
    smesh += a;
  }

  for (int i = 0; i < len; i++) {
    (*outmas)[schet[bymas[8 * i + byteN]]] = inmas[i];
    schet[bymas[8 * i + byteN]]++;
  }
}

void RadixSortAll(double**inmas, int len) {
  double* outmas = new double[len];
  RadixSortPart(*inmas, &outmas, len, 0);
  RadixSortPart(outmas, inmas, len, 1);
  RadixSortPart(*inmas, &outmas, len, 2);
  RadixSortPart(outmas, inmas, len, 3);
  RadixSortPart(*inmas, &outmas, len, 4);
  RadixSortPart(outmas, inmas, len, 5);
  RadixSortPart(*inmas, &outmas, len, 6);
  RadixSortPart(outmas, inmas, len, 7);
}

double* RandMas(int len, double low, double high) {
  if (len <= 0) {
    throw std::exception();
  }
  std::random_device ran;
  std::mt19937 g(ran());
  if (low >= high) {
    throw std::exception();
  }
  std::uniform_real_distribution<> range(low, high);
  double *mas = new double[len];
  for (int i = 0; i < len; i++) {
    mas[i] = range(g);
  }
  return mas;
}

void get_tree_task(double* inmas, int l, int r, task* prev_task,
  const std::vector<int>& part, task* task_mas[], bool is_begin) {
  if (r - l == 0) {
    int begin = ((l == 0) ? 0 : part[l - 1]);
    int len = part[l];
    if (l)
      len -= part[l - 1];
    sortTask* stask = new sortTask(inmas, begin, len);
    stask->ref = prev_task;
    task_mas[r] = stask;
  } else {
    int mid = (l + r) / 2 + 1;
    int indleft = 0;
    if (l)
      indleft = part[l - 1];
    int lenleft = part[mid - 1] - indleft;
    int indright = indleft + lenleft;
    int lenright = part[r] - part[mid - 1];
    mergeTask* mtask = new mergeTask(inmas, indleft, lenleft, indright, lenright);
    mtask->ref = prev_task;
    get_tree_task(inmas, mid, r, mtask, part, task_mas);
    get_tree_task(inmas, l, mid - 1, mtask, part, task_mas);
  }
}

void RadixSortAllParallel(double ** inmas, int len) {
  int count_threads = omp_get_max_threads();
  std::vector<task*>task_mas(count_threads);
  std::vector<task*> tasks;
  std::vector<int>part(count_threads);
  for (int i = 0; i < count_threads; i++) {
    part[i] = len / count_threads +
      (i < (len%count_threads) ? 1 : 0) + ((i == 0) ? 0 : part[i - 1]);
  }
  task* prev_task = nullptr;
  get_tree_task(*inmas, 0, count_threads - 1, prev_task, part, task_mas.data(), 1);
  while (task_mas.size()) {
#pragma omp parallel for
    for (int i = 0; i < static_cast<int>(task_mas.size()); i++) {
      task_mas[i]->do_task();
    }
    std::vector<task*>tmp_task_mas;
    for (int i = 0; i < static_cast<int>(task_mas.size()); i++) {
      if (task_mas[i]->ref == nullptr)
        continue;
      task_mas[i]->ref->count_depends--;
      if (task_mas[i]->ref->count_depends == 0)
        tmp_task_mas.push_back(task_mas[i]->ref);
      delete task_mas[i];
    }
    std::swap(tmp_task_mas, task_mas);
  }
}
