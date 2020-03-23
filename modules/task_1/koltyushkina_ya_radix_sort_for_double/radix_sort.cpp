// Copyright 2020 Koltyushkina Yanina

#include <iostream>
#include <random>
#include <stdexcept>
#include "../../../modules/task_1/koltyushkina_ya_radix_sort_for_double/radix_sort.h"

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

void RadixSortPart(double *inmas, double **outmas, int len, int byteN) {
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
