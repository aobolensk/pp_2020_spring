// Copyright 2020 Gaydaychuk Yury
#ifndef MODULES_TASK_2_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_
#define MODULES_TASK_2_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_
#include <omp.h>
#include <vector>
#include <string>
#include <list>
#include <utility>

class NetworkBuilder {
    std::list<std::vector<int> > auxiliaryNodeSetArray;
    std::list<std::vector<std::pair <int, int> > > parallelBlockArray;
    std::string state;
    int size = 0;
    int twoDegree = 0;
    std::vector<std::pair <int, int> > comparatorArray;
    std::vector<int> indexArray;
    void pseudoSort_2(int lo, int n);
    void bMerge_2(int lo, int n, int r);
    void printIndexArray();

    void addComparator(int i, int j);
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

bool checkAscending(std::vector<int> vec);
bool checkAscending(int *p, int length);
int getMax(std::vector<int> *vec);
int getMax(int *p, int length);
void sortByDigit(std::vector<int> *vec, int exp);
void sortByDigit(int *p, int length, int exp);
void bitwiseSort(std::vector<int> *vec);
void bitwiseSort(int *p, int length);
void bitwiseSortWithTiming(int *p, int length, double *time = nullptr);
void mergeAndSplit(int *arr1, int size1, int *arr2, int size2);
bool parallelBitwiseBatcherSort(int *array, int arraySize,
    int maxThreadCount, double *time = nullptr);
bool parallelBitwiseBatcherSort_for_timing(int *array, int arraySize,
    int maxThreadCount, double *time = nullptr);
bool parallelLocalSort(int *array, int arraySize, int maxThreadCount);

void printThreadNum(int maxThreadNumber);
void printThreadArea(int arraySize, int maxThreadCount);
#endif  // MODULES_TASK_2_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_
