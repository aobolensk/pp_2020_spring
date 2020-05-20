// Copyright 2020 Zhivaev Artem

#include "../../../modules/task_4/zhivaev_a_strassen/strassen_std_thread.h"

#include <bitset>
#include <stdexcept>
#include <thread>

void multSeq(int size, const double* a, const double* b, double* result);

void strassenRecursivePart(int size, const double* a, const double* b,
                           double* result);

void splitMatrix(int size, const double* a, double* a11, double* a12,
                 double* a21, double* a22);

void assembleMatrix(int size, double* a, const double* a11, const double* a12,
                    const double* a21, const double* a22);

// (A1 + A2)(B1 + B2)
void strassen1(int size, const double* a1, const double* a2, const double* b1,
               const double* b2, double* result);

// (A1 + A2)B
void strassen2(int size, const double* a1, const double* a2, const double* b,
               double* result);

// A(B1 - B2)
void strassen3(int size, const double* a, const double* b1, const double* b2,
               double* result);

// (A1 - A2)(B1 + B2)
void strassen4(int size, const double* a1, const double* a2, const double* b1,
               const double* b2, double* result);

int powerOf2(int number);

int nextPowerOf2(int number);

void multSeq(int size, const double* a, const double* b, double* result) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result[i * size + j] = 0.0;
      for (int k = 0; k < size; k++) {
        result[i * size + j] += a[i * size + k] * b[k * size + j];
      }
    }
  }
}

int powerOf2(int number) {
  if (number <= 0) {
    return -1;
  }
  std::bitset<sizeof(int) * 8> bits(number);
  if (bits.count() != 1) {
    return -1;
  }
  int count = static_cast<int>(bits.size());
  for (int i = 0; i < count; i++) {
    if (bits.test(i)) {
      return i;
    }
  }
  return -1;
}

int nextPowerOf2(int number) {
  if (number <= 1) {
    return -1;
  }
  if (powerOf2(number) != -1) {
    return number;
  }
  std::bitset<sizeof(int) * 8> bits(number);
  for (int i = static_cast<int>(bits.size() - 3); i != 0; i--) {
    if (bits.test(i)) {
      bits.reset();
      bits.set(i + 1);
      return static_cast<int>(bits.to_ulong());
    }
  }
  return -1;
}

void splitMatrix(int size, const double* a, double* a11, double* a12,
                 double* a21, double* a22) {
  int fSize = size / 2;
  for (int i = 0; i < fSize; i++) {
    for (int j = 0; j < fSize; j++) {
      a11[i * fSize + j] = a[i * size + j];
      a12[i * fSize + j] = a[i * size + fSize + j];
      a21[i * fSize + j] = a[(fSize + i) * size + j];
      a22[i * fSize + j] = a[(fSize + i) * size + fSize + j];
    }
  }
}

void assembleMatrix(int size, double* a, const double* a11, const double* a12,
                    const double* a21, const double* a22) {
  int fSize = size / 2;
  for (int i = 0; i < fSize; i++) {
    for (int j = 0; j < fSize; j++) {
      a[i * size + j] = a11[i * fSize + j];
      a[i * size + fSize + j] = a12[i * fSize + j];
      a[(fSize + i) * size + j] = a21[i * fSize + j];
      a[(fSize + i) * size + fSize + j] = a22[i * fSize + j];
    }
  }
}

void strassen1(int size, const double* a1, const double* a2, const double* b1,
               const double* b2, double* result) {
  double* t1 = new double[size * size * 2];
  double* t2 = t1 + size * size;
  int i;
  int length = size * size;

  for (i = 0; i < length; i++) {
    t1[i] = a1[i] + a2[i];
    t2[i] = b1[i] + b2[i];
  }

  strassenRecursivePart(size, t1, t2, result);

  delete[] t1;
}

void strassen2(int size, const double* a1, const double* a2, const double* b,
               double* result) {
  double* t = new double[size * size];
  int i;
  int length = size * size;

  for (i = 0; i < length; i++) {
    t[i] = a1[i] + a2[i];
  }

  strassenRecursivePart(size, t, b, result);

  delete[] t;
}

void strassen3(int size, const double* a, const double* b1, const double* b2,
               double* result) {
  double* t = new double[size * size];
  int i;
  int length = size * size;

  for (i = 0; i < length; i++) {
    t[i] = b1[i] - b2[i];
  }

  strassenRecursivePart(size, a, t, result);

  delete[] t;
}

void strassen4(int size, const double* a1, const double* a2, const double* b1,
               const double* b2, double* result) {
  double* t1 = new double[size * size * 2];
  double* t2 = t1 + size * size;
  int i;
  int length = size * size;

  for (i = 0; i < length; i++) {
    t1[i] = a1[i] - a2[i];
    t2[i] = b1[i] + b2[i];
  }

  strassenRecursivePart(size, t1, t2, result);

  delete[] t1;
}

void strassenRecursivePart(int size, const double* a, const double* b,
                           double* result) {
  if (size <= 128) {
    multSeq(size, a, b, result);
    return;
  }
  int qLength = size * size / 4;
  int i;
  double* a11 = new double[size * size];
  double* a12 = a11 + qLength;
  double* a21 = a12 + qLength;
  double* a22 = a21 + qLength;
  double* b11 = new double[size * size];
  double* b12 = b11 + qLength;
  double* b21 = b12 + qLength;
  double* b22 = b21 + qLength;
  double* c11 = new double[size * size];
  double* c12 = c11 + qLength;
  double* c21 = c12 + qLength;
  double* c22 = c21 + qLength;
  double* m1 = new double[qLength * 7];
  double* m2 = m1 + qLength;
  double* m3 = m2 + qLength;
  double* m4 = m3 + qLength;
  double* m5 = m4 + qLength;
  double* m6 = m5 + qLength;
  double* m7 = m6 + qLength;

  splitMatrix(size, a, a11, a12, a21, a22);
  splitMatrix(size, b, b11, b12, b21, b22);

  // M1 = (A11 + A22)(B11 + B22)
  //std::thread thread1([=] { strassen1(size / 2, a11, a22, b11, b22, m1); });
  std::thread thread1(strassen1, size / 2, a11, a22, b11, b22, m1);

  // M2 = (A21 + A22)B11
  //std::thread thread2([=] { strassen2(size / 2, a21, a22, b11, m2); });
  std::thread thread2(strassen2, size / 2, a21, a22, b11, m2);

  // M3 = A11(B12 - B22)
  //std::thread thread3([=] { strassen3(size / 2, a11, b12, b22, m3); });
  std::thread thread3(strassen3, size / 2, a11, b12, b22, m3);

  // M4 = A22(B21 - B11)
  //std::thread thread4([=] { strassen3(size / 2, a22, b21, b11, m4); });
  std::thread thread4(strassen3, size / 2, a22, b21, b11, m4);

  // M5 = (A11 + A12)B22
  //std::thread thread5([=] { strassen2(size / 2, a11, a12, b22, m5); });
  std::thread thread5(strassen2, size / 2, a11, a12, b22, m5);

  // M6 = (A21 - A11)(B11 + B12)
  //std::thread thread6([=] { strassen4(size / 2, a21, a11, b11, b12, m6); });
  std::thread thread6(strassen4, size / 2, a21, a11, b11, b12, m6);

  // M7 = (A12 - A22)(B21 + B22)
  //std::thread thread7([=] { strassen4(size / 2, a12, a22, b21, b22, m7); });
  std::thread thread7(strassen4, size / 2, a12, a22, b21, b22, m7);

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();
  thread5.join();
  thread6.join();
  thread7.join();

  // C11 = M1 + M4 - M5 + M7
  for (i = 0; i < qLength; i++) {
    c11[i] = m1[i] + m4[i] - m5[i] + m7[i];
  }

  // C12 = M3 + M5
  for (i = 0; i < qLength; i++) {
    c12[i] = m3[i] + m5[i];
  }

  // C21 = M2 + M4
  for (i = 0; i < qLength; i++) {
    c21[i] = m2[i] + m4[i];
  }

  // C22 = M1 - M2 + M3 + M6
  for (i = 0; i < qLength; i++) {
    c22[i] = m1[i] - m2[i] + m3[i] + m6[i];
  }

  assembleMatrix(size, result, c11, c12, c21, c22);

  delete[] a11;
  delete[] b11;
  delete[] c11;
  delete[] m1;
}

void strassenMultStdThread(int size, const double* a, const double* b,
                           double* result) {
  if (powerOf2(size) < 0) {
    throw std::invalid_argument("");
  }

  strassenRecursivePart(size, a, b, result);
}
