// Copyright 2020 Rezantsev Sergey
#include "../../modules/task_4/rezantsev_s_strassen_std/strassen.h"
#include <math.h>
#include <algorithm>
#include <future>
#include <mutex>
#include <thread>
#include <vector>
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

bool isEqMatrix(std::vector<double> a, std::vector<double> b, int n) {
  bool f = true;
  for (int i = 0; i < n * n; i++)
    if (a[i] != b[i]) {
      f = false;
      break;
    }
  return f;
}

void splitMatrix(std::vector<double> a, std::vector<double> *a11,
                 std::vector<double> *a22, std::vector<double> *a12,
                 std::vector<double> *a21, int n) {
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

void sum(const std::vector<double> &a, const std::vector<double> &b,
         std::vector<double> *c) {
  for (unsigned int i = 0; i < c->size(); i++) c->at(i) = a[i] + b[i];
}

void multMatrix(const std::vector<double> &a, const std::vector<double> &b,
                std::vector<double> *c, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        c->at(i * n + j) += a[i * n + k] * b[k * n + j];
      }
    }
  }
}

static int DEEP = 0;

void strassen_std(const std::vector<double> &a, const std::vector<double> &b,
                  std::vector<double> *result) {
  int n = sqrt(result->size());
  if (n <= 2) {
    multMatrix(a, b, result, n);
    return;
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
  std::vector<double> r11(n * n);
  std::vector<double> r12(n * n);
  std::vector<double> r21(n * n);
  std::vector<double> r22(n * n);
  std::vector<double> p1(n * n);
  std::vector<double> p2(n * n);
  std::vector<double> p3(n * n);
  std::vector<double> p4(n * n);
  std::vector<double> p5(n * n);
  std::vector<double> p6(n * n);
  std::vector<double> p7(n * n);

  std::thread splitA(splitMatrix, a, &a11, &a22, &a12, &a21, n * 2);
  std::thread splitB(splitMatrix, b, &b11, &b22, &b12, &b21, n * 2);
  splitA.join();
  splitB.join();
  DEEP++;
  if (DEEP < 2) {
    std::thread treads[4] = {
        std::thread(strassen_std, sumMatrix(a11, a22, n),
                    sumMatrix(b11, b22, n), &p1),
        std::thread(strassen_std, sumMatrix(a21, a22, n), b11, &p2),
        std::thread(strassen_std, a11, subtMatrix(b12, b22, n), &p3),
        std::thread(strassen_std, a22, subtMatrix(b21, b11, n), &p4),
    };

    for (int i = 0; i < 4; i++) treads[i].join();
    std::thread treadss[3] = {
        std::thread(strassen_std, sumMatrix(a11, a12, n), b22, &p5),
        std::thread(strassen_std, subtMatrix(a21, a11, n),
                    sumMatrix(b11, b12, n), &p6),
        std::thread(strassen_std, subtMatrix(a12, a22, n),
                    sumMatrix(b21, b22, n), &p7)};

    for (int i = 0; i < 3; i++) treadss[i].join();
    std::thread restreads[4] = {
        std::thread(sum, p3, p5, &r12), std::thread(sum, p2, p4, &r21),
        std::thread(sum, sumMatrix(p1, p4, n), subtMatrix(p7, p5, n), &r11),
        std::thread(sum, subtMatrix(p1, p2, n), sumMatrix(p3, p6, n), &r22)};
    for (int i = 0; i < 4; i++) restreads[i].join();
  } else {
    p1 = strassen(sumMatrix(a11, a22, n), sumMatrix(b11, b22, n), n);
    p2 = strassen(sumMatrix(a21, a22, n), b11, n);
    p3 = strassen(a11, subtMatrix(b12, b22, n), n);
    p4 = strassen(a22, subtMatrix(b21, b11, n), n);
    p5 = strassen(sumMatrix(a11, a12, n), b22, n);
    p6 = strassen(subtMatrix(a21, a11, n), sumMatrix(b11, b12, n), n);
    p7 = strassen(subtMatrix(a12, a22, n), sumMatrix(b21, b22, n), n);
    r11 = sumMatrix(sumMatrix(p1, p4, n), subtMatrix(p7, p5, n), n);
    r12 = sumMatrix(p3, p5, n);
    r21 = sumMatrix(p2, p4, n);
    r22 = sumMatrix(subtMatrix(p1, p2, n), sumMatrix(p3, p6, n), n);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result->at(i * (n * 2) + j) = r11[i * n + j];
      result->at(i * (n * 2) + j + n) = r12[i * n + j];
      result->at((i + n) * (n * 2) + j) = r21[i * n + j];
      result->at((i + n) * (n * 2) + j + n) = r22[i * n + j];
    }
  }
  DEEP--;
}
