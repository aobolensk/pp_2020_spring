// Copyright 2020 Rezantsev Sergey
#include <omp.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include "../../modules/task_2/rezantsev_s_strassen_omp/strassen.h"
std::vector<double> sumMatrix(std::vector<double> a, std::vector<double> b,
                              int n) {
  std::vector<double> res(n * n);
  for (int i = 0; i < n * n; i++) res[i] = a[i] + b[i];
  return res;
}

int checkSize(int n) {
  int m = 2;
  while (n > m) m = m * 2;
  return m;
}

std::vector<double> resizeMatrix(std::vector<double> a, int n) {
  int m = checkSize(n);
  std::vector<double> b(m * m);
  for (int i = 0; i < m * m; i++) b[i] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      b[i * m + j] = a[i * n + j];
    }
  }
  return b;
}

std::vector<double> subtMatrix(std::vector<double> a, std::vector<double> b,
                               int n) {
  std::vector<double> res(n * n);
  for (int i = 0; i < n * n; i++) res[i] = a[i] - b[i];
  return res;
}

std::vector<double> multMatrix(std::vector<double> a, std::vector<double> b,
                               int n) {
  std::vector<double> res(n * n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res[i * n + j] = 0;
      for (int k = 0; k < n; k++) {
        res[i * n + j] += a[i * n + k] * b[k * n + j];
      }
    }
  }
  return res;
}
void splitMatrix(std::vector<double> a, std::vector<double>* a11,
                 std::vector<double>* a22, std::vector<double>* a12,
                 std::vector<double>* a21, int n) {
  int m = n / 2;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      a11->at(i * m + j) = a[i * n + j];
      a12->at(i * m + j) = a[i * n + j + m];
      a21->at(i * m + j) = a[(i + m) * n + j];
      a22->at(i * m + j) = a[(i + m) * n + j + m];
    }
  }
}

std::vector<double> collectMatrix(std::vector<double> a11,
                                  std::vector<double> a22,
                                  std::vector<double> a12,
                                  std::vector<double> a21, int m) {
  int n = m * 2;
  std::vector<double> a(n * n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      a[i * n + j] = a11[i * m + j];
      a[i * n + j + m] = a12[i * m + j];
      a[(i + m) * n + j] = a21[i * m + j];
      a[(i + m) * n + j + m] = a22[i * m + j];
    }
  }
  return a;
}

void sumMatrix(const std::vector<double>& a, const std::vector<double>& b,
               std::vector<double> *c) {
  for (unsigned int i = 0; i < c->size(); i++) c->at(i) = a[i] + b[i];
}

void subtMatrix(const std::vector<double>& a, const std::vector<double>& b,
                std::vector<double> *c) {
  for (unsigned int i = 0; i < c->size(); i++) c->at(i) = a[i] - b[i];
}

void multMatrix(const std::vector<double>& a, const std::vector<double>& b,
                std::vector<double> *c, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        c->at(i * n + j) += a[i * n + k] * b[k * n + j];
      }
    }
  }
}

bool isEqMatrix(std::vector<double> a, std::vector<double> b, int n) {
  bool f = true;
  for (int i = 0; i < n * n; i++)
    if (a[i] != b[i]) {
      f = false;
      break;
    }
  return f;
}

std::vector<double> strassen(std::vector<double> a, std::vector<double> b,
                             int n) {
  if (n <= 2) {
    return multMatrix(a, b, n);
  }
  n = n / 2;
  std::vector<double> a11(n * n);
  std::vector<double> a12(n * n);
  std::vector<double> a21(n * n);
  std::vector<double> a22(n * n);
  std::vector<double> b11(n * n);
  std::vector<double> b12(n * n);
  std::vector<double> b21(n * n);
  std::vector<double> b22(n * n);

  splitMatrix(a, &a11, &a22, &a12, &a21, n * 2);
  splitMatrix(b, &b11, &b22, &b12, &b21, n * 2);

  std::vector<double> p1 =
      strassen(sumMatrix(a11, a22, n), sumMatrix(b11, b22, n), n);
  std::vector<double> p2 = strassen(sumMatrix(a21, a22, n), b11, n);
  std::vector<double> p3 = strassen(a11, subtMatrix(b12, b22, n), n);
  std::vector<double> p4 = strassen(a22, subtMatrix(b21, b11, n), n);
  std::vector<double> p5 = strassen(sumMatrix(a11, a12, n), b22, n);
  std::vector<double> p6 =
      strassen(subtMatrix(a21, a11, n), sumMatrix(b11, b12, n), n);
  std::vector<double> p7 =
      strassen(subtMatrix(a12, a22, n), sumMatrix(b21, b22, n), n);

  b11 = sumMatrix(sumMatrix(p1, p4, n), subtMatrix(p7, p5, n), n);
  b12 = sumMatrix(p3, p5, n);
  b21 = sumMatrix(p2, p4, n);
  b22 = sumMatrix(subtMatrix(p1, p2, n), sumMatrix(p3, p6, n), n);

  return collectMatrix(b11, b22, b12, b21, n);
}


void strassen_omp(const std::vector<double>& a, const std::vector<double>& b,
              std::vector<double>* result) {
  int n = sqrt(result->size());
  const int m1 = n;
  if (n <= 2) {
    multMatrix(a, b, result, n);
    return;
  }
  const int h = m1 / 2;
  std::vector<double> a11(h * h);
  std::vector<double> a12(h * h);
  std::vector<double> a21(h * h);
  std::vector<double> a22(h * h);
  std::vector<double> b11(h * h);
  std::vector<double> b12(h * h);
  std::vector<double> b21(h * h);
  std::vector<double> b22(h * h);
  std::vector<double> r11(h * h);
  std::vector<double> r12(h * h);
  std::vector<double> r21(h * h);
  std::vector<double> r22(h * h);
  std::vector<double> p1(h * h);
  std::vector<double> p2(h * h);
  std::vector<double> p3(h * h);
  std::vector<double> p4(h * h);
  std::vector<double> p5(h * h);
  std::vector<double> p6(h * h);
  std::vector<double> p7(h * h);
#pragma omp parallel for default(shared)
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < h; j++) {
      a11[i * h + j] = a[i * n + j];
      a12[i * h + j] = a[i * n + j + h];
      a21[i * h + j] = a[(i + h) * n + j];
      a22[i * h + j] = a[(i + h) * n + j + h];
      b11[i * h + j] = b[i * n + j];
      b12[i * h + j] = b[i * n + j + h];
      b21[i * h + j] = b[(i + h) * n + j];
      b22[i * h + j] = b[(i + h) * n + j + h];
    }
  }
#pragma omp parallel sections default(shared)
  {
#pragma omp section
    {
      std::vector<double> t1(h * h);
      std::vector<double> t2(h * h);
      sumMatrix(a11, a22, &t1);
      sumMatrix(b11, b22, &t2);
      strassen_omp(t1, t2, &p1);
    }
#pragma omp section
    {
      std::vector<double> t1(h * h);
      sumMatrix(a21, a22, &t1);
      strassen_omp(t1, b11, &p2);
    }
#pragma omp section
    {
      std::vector<double> t1(h * h);
      subtMatrix(b12, b22, &t1);
      strassen_omp(a11, t1, &p3);
    }
#pragma omp section
    {
      std::vector<double> t1(h * h);
      subtMatrix(b21, b11, &t1);
      strassen_omp(a22, t1, &p4);
    }
#pragma omp section
    {
      std::vector<double> t1(h * h);
      sumMatrix(a11, a12, &t1);
      strassen_omp(t1, b22, &p5);
    }
#pragma omp section
    {
      std::vector<double> t1(h * h);
      std::vector<double> t2(h * h);
      subtMatrix(a21, a11, &t1);
      sumMatrix(b11, b12, &t2);
      strassen_omp(t1, t2, &p6);
    }
#pragma omp section
    {
      std::vector<double> t1(h * h);
      std::vector<double> t2(h * h);
      subtMatrix(a12, a22, &t1);
      sumMatrix(b21, b22, &t2);
      strassen_omp(t1, t2, &p7);
    }
  }
  sumMatrix(p3, p5, &r12);
  sumMatrix(p2, p4, &r21);
  std::vector<double> t1(h * h);
  std::vector<double> t2(h * h);
  sumMatrix(p1, p4, &t1);
  sumMatrix(t1, p7, &t2);
  subtMatrix(t2, p5, &r11);

  std::vector<double> t3(h * h);
  std::vector<double> t4(h * h);
  sumMatrix(p1, p3, &t3);
  sumMatrix(t3, p6, &t4);
  subtMatrix(t4, p2, &r22);
#pragma omp parallel for default(shared)
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < h; j++) {
      result->at(i * n + j) = r11[i * h + j];
      result->at(i * n + j + h) = r12[i * h + j];
      result->at((i + h) * n + j) = r21[i * h + j];
      result->at((i + h) * n + j + h) = r22[i * h + j];
    }
  }
}
