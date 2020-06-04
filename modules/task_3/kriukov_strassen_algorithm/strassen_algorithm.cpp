// Copyright 2020 Kriukov Dmitry

#include <../../../modules/task_3/kriukov_strassen_algorithm/strassen_algorithm.h>
#include <tbb/tbb.h>
#include <random>
#include <ctime>
#include <vector>

std::vector<double> getRandomMatrix(int sz) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<double> vec(sz*sz);
  for (int i = 0; i < sz*sz; i++) {
    vec[i] = gen() % 9 + 1;
  }
  return vec;
}

std::vector<double> regularMultiplication(const std::vector<double>& a, const std::vector<double>& b, unsigned int sz) {
  std::vector<double> res(sz* sz);
  for (unsigned int i = 0; i < sz; i++)
    for (unsigned int j = 0; j < sz; j++) {
      for (unsigned int k = 0; k < sz; k++)
        res[j + i * sz] += a[i * sz + k] * b[j + k * sz];
    }
  return res;
}

std::vector<double> sum(const std::vector<double>& a, const std::vector<double>& b, unsigned int sz) {
  unsigned int size = sz * sz;
  std::vector<double> res(size);
  for (unsigned int i = 0; i < size; i++) {
    res[i] = a[i] + b[i];
  }
  return res;
}

std::vector<double> diff(const std::vector<double>& a, const std::vector<double>& b, unsigned int sz) {
  unsigned int size = sz * sz;
  std::vector<double> res(size);
  for (unsigned int i = 0; i < size; i++) {
    res[i] = a[i] - b[i];
  }
  return res;
}

void splitMatrix(const std::vector<double> &mtx, std::vector<double> *a,
                 std::vector<double> *b, std::vector<double> *c, std::vector<double> *d, unsigned int size) {
  unsigned int sz = size / 2;
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * 2 * sz; j < i * 2 * sz + sz; j++)
      a->push_back(mtx[j]);
    for (unsigned int j = i * 2 * sz + sz; j < i * 2 * sz + 2 * sz; j++)
      b->push_back(mtx[j]);
  }
  for (unsigned int i = sz; i < 2*sz; i++) {
    for (unsigned int j = i * 2 * sz; j < i * 2 * sz + sz; j++)
      c->push_back(mtx[j]);
    for (unsigned int j = i * 2 * sz + sz; j < i * 2 * sz + 2 * sz; j++)
      d->push_back(mtx[j]);
  }
}

void mergeMatrix(std::vector<double> *mtx, const std::vector<double> &a, const std::vector<double> &b,
                 const std::vector<double> &c, const std::vector<double> &d, unsigned int size) {
  unsigned int sz = size / 2;
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx->push_back(a[j]);
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx->push_back(b[j]);
  }
  for (unsigned int i = 0; i < sz; i++) {
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx->push_back(c[j]);
    for (unsigned int j = i * sz; j < i * sz + sz; j++)
      mtx->push_back(d[j]);
  }
}

std::vector<double> toPowerOfTwoSize(const std::vector<double>& mtx, unsigned int sz) {
  unsigned int power = 2;
  while (sz > power)
    power *= 2;
  std::vector<double> res;
  for (unsigned i = 0; i < sz; i++) {
    for (unsigned j = 0; j < sz; j++)
      res.push_back(mtx[j + i * sz]);
    for (unsigned j = sz; j < power; j++)
      res.push_back(0);
  }
  for (unsigned i = sz; i < power; i++) {
    for (unsigned j = 0; j < power; j++)
      res.push_back(0);
  }
  return res;
}

std::vector<double> toPowerOfTwoSize(const std::vector<double> &mtx, unsigned* power, unsigned int sz) {
  *power = 2;
  while (sz > *power)
    *power *= 2;
  unsigned tpow = *power;
  std::vector<double> res;
  for (unsigned i = 0; i < sz; i++) {
    for (unsigned j = 0; j < sz; j++)
      res.push_back(mtx[j + i * sz]);
    for (unsigned j = sz; j < tpow; j++)
      res.push_back(0);
  }
  for (unsigned i = sz; i < tpow; i++) {
    for (unsigned j = 0; j < tpow; j++)
      res.push_back(0);
  }
  return res;
}

std::vector<double> matrixReduce(const std::vector<double>& mtx, unsigned int sz) {
  std::vector<double> res(sz*sz);
  unsigned mtxsize = static_cast<unsigned>(std::sqrt(mtx.size()));

  for (unsigned i = 0; i < sz; i++)
    for (unsigned j = 0; j < sz; j++) {
      res[i * sz + j] = mtx[i * mtxsize + j];
    }

  return res;
}

std::vector<double> strassenMultiplication_tbb(const std::vector<double>& a,
                                           const std::vector<double>& b, unsigned int sz) {
  unsigned tpow;
  std::vector<double> a_ = toPowerOfTwoSize(a, &tpow, sz);
  std::vector<double> b_ = toPowerOfTwoSize(b, sz);
  std::vector<double> res;

  res = strassenMultiplication_NoCastToPowerOfTwo_tbb(a_, b_, tpow);

  return matrixReduce(res, sz);
}

std::vector<double> strassenMultiplication_NoCastToPowerOfTwo_tbb(const std::vector<double>& a_,
                    const std::vector<double>& b_, unsigned int sz) {
  std::vector<double> res;

  std::vector<double> a11, a12, a21, a22;
  std::vector<double> b11, b12, b21, b22;
  std::vector<double> p1, p2, p3, p4, p5, p6, p7;

  unsigned int split_sz = sz / 2;

  splitMatrix(a_, &a11, &a12, &a21, &a22, sz);
  splitMatrix(b_, &b11, &b12, &b21, &b22, sz);

  tbb::task_group group;

  if (a11.size() > 256) {
    group.run([&] {
      p1 = strassenMultiplication_NoCastToPowerOfTwo_tbb(sum(a11, a22, split_sz),
        sum(b11, b22, split_sz), split_sz);
    });
    group.run([&] {
      p2 = strassenMultiplication_NoCastToPowerOfTwo_tbb(sum(a21, a22, split_sz), b11, split_sz);
    });
    group.run([&] {
      p3 = strassenMultiplication_NoCastToPowerOfTwo_tbb(a11, diff(b12, b22, split_sz), split_sz);
    });
    group.run([&] {
      p4 = strassenMultiplication_NoCastToPowerOfTwo_tbb(a22, diff(b21, b11, split_sz), split_sz);
    });
    group.run([&] {
      p5 = strassenMultiplication_NoCastToPowerOfTwo_tbb(sum(a11, a12, split_sz),
          b22, split_sz);
    });
    group.run([&] {
      p6 = strassenMultiplication_NoCastToPowerOfTwo_tbb(diff(a21, a11, split_sz),
        sum(b11, b12, split_sz), split_sz);
    });
    group.run([&] {
      p7 = strassenMultiplication_NoCastToPowerOfTwo_tbb(diff(a12, a22, split_sz),
        sum(b21, b22, split_sz), split_sz);
    });
    group.wait();
  } else {
    p1 = regularMultiplication(sum(a11, a22, split_sz), sum(b11, b22, split_sz), split_sz);
    p2 = regularMultiplication(sum(a21, a22, split_sz), b11, split_sz);
    p3 = regularMultiplication(a11, diff(b12, b22, split_sz), split_sz);
    p4 = regularMultiplication(a22, diff(b21, b11, split_sz), split_sz);
    p5 = regularMultiplication(sum(a11, a12, split_sz), b22, split_sz);
    p6 = regularMultiplication(diff(a21, a11, split_sz), sum(b11, b12, split_sz), split_sz);
    p7 = regularMultiplication(diff(a12, a22, split_sz), sum(b21, b22, split_sz), split_sz);
  }

  std::vector<double> c11, c12, c21, c22;

  c11 = sum(diff(sum(p1, p4, split_sz), p5, split_sz), p7, split_sz);
  c12 = sum(p3, p5, split_sz);
  c21 = sum(p2, p4, split_sz);
  c22 = sum(sum(diff(p1, p2, split_sz), p3, split_sz), p6, split_sz);

  mergeMatrix(&res, c11, c12, c21, c22, sz);

  return res;
}

std::vector<double> strassenMultiplication(const std::vector<double>& a,
  const std::vector<double>& b, unsigned int sz) {
  unsigned tpow;
  std::vector<double> a_ = toPowerOfTwoSize(a, &tpow, sz);
  std::vector<double> b_ = toPowerOfTwoSize(b, sz);

  std::vector<double> res = strassenMultiplication_NoCastToPowerOfTwo(a_, b_, tpow);

  return matrixReduce(res, sz);
}

std::vector<double> strassenMultiplication_NoCastToPowerOfTwo(const std::vector<double>& a_,
  const std::vector<double>& b_, unsigned int sz) {
  std::vector<double> res;

  std::vector<double> a11, a12, a21, a22;
  std::vector<double> b11, b12, b21, b22;

  splitMatrix(a_, &a11, &a12, &a21, &a22, sz);
  splitMatrix(b_, &b11, &b12, &b21, &b22, sz);

  unsigned int split_sz = sz / 2;

  std::vector<double> p1, p2, p3, p4, p5, p6, p7;


  if (a11.size() > 256) {
    p1 = strassenMultiplication_NoCastToPowerOfTwo(sum(a11, a22, split_sz), sum(b11, b22, split_sz), split_sz);
    p2 = strassenMultiplication_NoCastToPowerOfTwo(sum(a21, a22, split_sz), b11, split_sz);
    p3 = strassenMultiplication_NoCastToPowerOfTwo(a11, diff(b12, b22, split_sz), split_sz);
    p4 = strassenMultiplication_NoCastToPowerOfTwo(a22, diff(b21, b11, split_sz), split_sz);
    p5 = strassenMultiplication_NoCastToPowerOfTwo(sum(a11, a12, split_sz), b22, split_sz);
    p6 = strassenMultiplication_NoCastToPowerOfTwo(diff(a21, a11, split_sz), sum(b11, b12, split_sz), split_sz);
    p7 = strassenMultiplication_NoCastToPowerOfTwo(diff(a12, a22, split_sz), sum(b21, b22, split_sz), split_sz);
  } else {
    p1 = regularMultiplication(sum(a11, a22, split_sz), sum(b11, b22, split_sz), split_sz);
    p2 = regularMultiplication(sum(a21, a22, split_sz), b11, split_sz);
    p3 = regularMultiplication(a11, diff(b12, b22, split_sz), split_sz);
    p4 = regularMultiplication(a22, diff(b21, b11, split_sz), split_sz);
    p5 = regularMultiplication(sum(a11, a12, split_sz), b22, split_sz);
    p6 = regularMultiplication(diff(a21, a11, split_sz), sum(b11, b12, split_sz), split_sz);
    p7 = regularMultiplication(diff(a12, a22, split_sz), sum(b21, b22, split_sz), split_sz);
  }

  std::vector<double> c11, c12, c21, c22;

  c11 = sum(diff(sum(p1, p4, split_sz), p5, split_sz), p7, split_sz);
  c12 = sum(p3, p5, split_sz);
  c21 = sum(p2, p4, split_sz);
  c22 = sum(sum(diff(p1, p2, split_sz), p3, split_sz), p6, split_sz);

  mergeMatrix(&res, c11, c12, c21, c22, sz);

  return res;
}
