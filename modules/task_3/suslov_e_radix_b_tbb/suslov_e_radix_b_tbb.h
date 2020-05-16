// Copyright 2020 Suslov Egor
#ifndef MODULES_TASK_3_SUSLOV_E_RADIX_B_TBB_SUSLOV_E_RADIX_B_TBB_H_
#define MODULES_TASK_3_SUSLOV_E_RADIX_B_TBB_SUSLOV_E_RADIX_B_TBB_H_

#include <vector>
#include <string>
#include "tbb/tbb.h"

double* getRandomArray(int size);
void CountingSortByte(double* inp, double* out, int byteNum, int size);
void LSDSortDouble(double* inp, double* tmp, int size);
class EvenSplitter;
class OddSplitter;
class SimpleComparator;
class LSDParallelSorter;
void LSDParallelSortDouble(double* inp, int size, int nThreads);
bool CompareArrays(double* mas, double* Mas, int size);

#endif  // MODULES_TASK_3_SUSLOV_E_RADIX_B_TBB_SUSLOV_E_RADIX_B_TBB_H_


