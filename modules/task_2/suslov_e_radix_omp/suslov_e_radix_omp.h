// Copyright 2020 Suslov Egor
#ifndef MODULES_TASK_2_SUSLOV_E_RADIX_OMP_SUSLOV_E_RADIX_OMP_H_
#define MODULES_TASK_2_SUSLOV_E_RADIX_OMP_SUSLOV_E_RADIX_OMP_H_

#include <vector>
#include <string>

void CountingSortByte(double* inp, double* out, int byteNum, int size);
void LSDSortDouble(double* inp, double* tmp, int size);
double* getRandomArray(int sz);
bool CompareArrays(double* mas, double* gMas, int size);
void EvenSplitter(double* mas, double* tmp, int size1, int size2);
void OddSplitter(double* mas, double* tmp, int size1, int size2);
void SimpleComparator(double* mas, int size);
void LSDParallelSorter(double* mas, double* tmp, int size, int portion);
void LSDParallelSortDouble(double* inp, int size, int nThreads);
double* array_double_copy(double* Array, int size);

#endif  // MODULES_TASK_2_SUSLOV_E_RADIX_OMP_SUSLOV_E_RADIX_OMP_H_
