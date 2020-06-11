// Copyright 2018 Nesterov Alexander
#ifndef MODULES_TASK_4_SUSLOV_E_BATCHERS_SORT_SUSLOV_E_BATCHERS_SORT_H_
#define MODULES_TASK_4_SUSLOV_E_BATCHERS_SORT_SUSLOV_E_BATCHERS_SORT_H_

#include <vector>
#include <string>

void CountingSortByte(double* inp, double* out, int byteNum, int size);
void LSDSortDouble(double* inp, double* tmp, int size);
double* getRandomArray(int sz);
std::vector<int> getRandomVector(int sz);
bool CompareArrays(double* mas, double* gMas, int size);
void EvenSplitter(double* mas, double* tmp, int size1, int size2);
void OddSplitter(double* mas, double* tmp, int size1, int size2);
void SimpleComparator(double* mas, int size);
void LSDParallelSortDouble(double* inp, int size, int nThreads);
void LSDParallelSorter(double* mas, double* tmp, int size, int portion);
double* array_double_copy(double* Array, int size);

#endif  // MODULES_TASK_4_SUSLOV_E_BATCHERS_SORT_SUSLOV_E_BATCHERS_SORT_H_
