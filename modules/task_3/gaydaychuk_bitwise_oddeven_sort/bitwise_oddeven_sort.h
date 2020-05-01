// Copyright 2020 Gaydaychuk Yury
#ifndef MODULES_TASK_3_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_
#define MODULES_TASK_3_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_
#define MINIMAL_SINGLE_ARRAY_LENGTH 2

#include <tbb/tbb.h>
#include <utility>
#include <list>
#include <vector>
#include <string>

class Hello;

class HelloTask : public tbb::task {
  int i;
  int j;
 public:
  HelloTask(int _i, int _j) : i(_i), j(_j) {}
  task* execute();
};

class SortSubarrayTask : public tbb::task {
  int taskId;
  int taskCount;
  int size;
  int *array;
  int bI;
  int eI;
 public:
  SortSubarrayTask(int *pArray,
      int threadNumber, int effectiveThreadCount,
      int arraySize) : taskId(threadNumber),
    taskCount(effectiveThreadCount),
    size(arraySize), array(pArray) {}
  task* execute();
};

class MergeSubarraysTask : public tbb::task {
  int *array1;
  int size1;
  int *array2;
  int size2;
 public:
  MergeSubarraysTask(int *_array1, int _size1,
  int *_array2, int _size2) : array1(_array1),
    size1(_size1), array2(_array2), size2(_size2) {}
  task* execute();
};

class NetworkBuilder {
    std::list<std::vector<int> > auxiliaryNodeSetArray;
    std::list<std::vector<std::pair <int, int> > > parallelBlockArray;
    int size = 0;
    int twoDegree = 0;
    std::vector<std::pair <int, int> > comparatorArray;
    std::vector<int> indexArray;
    void pseudoSort(int lo, int n);
    void bMerge(int lo, int n, int r);

    void addComparatorAnother(int i, int j);
 public:
    void setNetworkSize(int size);
    void computeNetwork();
    std::list<std::vector<std::pair <int, int> > > getParallelBlockArray();
    std::string printComp();
    std::string printParallelComp();
    std::string printAux();
    std::string getState();
};

std::vector<int> getRandomVector(int sz);
bool checkAscending(int *p, int length);
int getMax(int *p, int length);
void sortByDigit(int *p, int length, int exp);
void bitwiseSort(int *p, int length, double *time = nullptr);
void parallelLocalSort(int *p, int length, int chunksCount,
  double *time = nullptr);
int getEffectiveUnitCount(int arraySize, int maxThreadCount,
    int minimalSubarrayLength = MINIMAL_SINGLE_ARRAY_LENGTH);
void mergeAndSplit(int *arr1, int size1, int *arr2, int size2);
void tbbHello(int i);
void getLocalArea(
    int threadNumber, int effectiveThreadCount,
    int arraySize,
    int *beginIndex, int *endIndex);
#endif  // MODULES_TASK_3_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_
