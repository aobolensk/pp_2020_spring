// Copyright 2020 Rezantsev Sergey
#include "../../modules/task_1/rezantsev_s_strassen/strassen.h"
#include <algorithm>

double* sumMatrix(double* a, double* b, int n) {
  double* res = new double[n * n];
  for (int i = 0; i < n * n; i++) res[i] = a[i] + b[i];
  return res;
}

double* subtMatrix(double* a, double* b, int n) {
  double* res = new double[n * n];
  for (int i = 0; i < n * n; i++) res[i] = a[i] - b[i];
  return res;
}

double* multMatrix(double* a, double* b, int n) {
  double* res = new double[n * n];
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

bool isEqMatrix(double* a, double* b, int n) {
  bool f = true;
  for (int i = 0; i < n * n; i++)
    if (a[i] != b[i]) {
      f = false;
      break;
    }
  return f;
}

void splitMatrix(double* a, double* a11, double* a22, double* a12, double* a21,
                 int n) {
  int m = n / 2;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      a11[i * m + j] = a[i * n + j];
      a12[i * m + j] = a[i * n + j + m];
      a21[i * m + j] = a[(i + m) * n + j];
      a22[i * m + j] = a[(i + m) * n + j + m];
    }
  }
}

double* collectMatrix(double* a11, double* a22, double* a12, double* a21,
                      int m) {
  int n = m * 2;
  double* a = new double[n * n];
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

double* strassen(double* a, double* b, int n) {
  if (n <= 2) {
    return multMatrix(a, b, n);
  }
  n = n / 2;
  double* a11 = new double[n * n];
  double* a12 = new double[n * n];
  double* a21 = new double[n * n];
  double* a22 = new double[n * n];
  double* b11 = new double[n * n];
  double* b12 = new double[n * n];
  double* b21 = new double[n * n];
  double* b22 = new double[n * n];

  splitMatrix(a, a11, a22, a12, a21, n * 2);
  splitMatrix(b, b11, b22, b12, b21, n * 2);

  double* p1 = strassen(sumMatrix(a11, a22, n), sumMatrix(b11, b22, n), n);
  double* p2 = strassen(sumMatrix(a21, a22, n), b11, n);
  double* p3 = strassen(a11, subtMatrix(b12, b22, n), n);
  double* p4 = strassen(a22, subtMatrix(b21, b11, n), n);
  double* p5 = strassen(sumMatrix(a11, a12, n), b22, n);
  double* p6 = strassen(subtMatrix(a21, a11, n), sumMatrix(b11, b12, n), n);
  double* p7 = strassen(subtMatrix(a12, a22, n), sumMatrix(b21, b22, n), n);

  double* c11 = sumMatrix(sumMatrix(p1, p4, n), subtMatrix(p7, p5, n), n);
  double* c12 = sumMatrix(p3, p5, n);
  double* c21 = sumMatrix(p2, p4, n);
  double* c22 = sumMatrix(subtMatrix(p1, p2, n), sumMatrix(p3, p6, n), n);

  return collectMatrix(c11, c22, c12, c21, n);
}