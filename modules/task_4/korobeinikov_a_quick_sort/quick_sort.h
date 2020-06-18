// Copyright 2020 Korobeinikov Aleksei
#ifndef MODULES_TASK_4_KOROBEINIKOV_A_QUICK_SORT_QUICK_SORT_H_
#define MODULES_TASK_4_KOROBEINIKOV_A_QUICK_SORT_QUICK_SORT_H_
#include <vector>


class EvenSplitter {
 private:
    double* mas;
    double* tmp;
    int size1;
    int size2;
 public:
    EvenSplitter(double* _mas, double* _tmp, int _size1,
        int _size2) : mas(_mas), tmp(_tmp),
        size1(_size1), size2(_size2)
    {}
    void operator()();
};

class OddSplitter {
 private:
    double* mas;
    double* tmp;
    int size1;
    int size2;
 public:
    OddSplitter(double* _mas, double* _tmp, int _size1,
        int _size2) : mas(_mas), tmp(_tmp),
        size1(_size1), size2(_size2)
    {}
    void operator()();
};

class SimpleComparator {
 private:
    double* mas;
 public:
    explicit SimpleComparator(double* _mas) : mas(_mas)
    {}
    void operator()(int start, int finish) const;
};

class QuickParallelSorter {
 private:
    double* mas;
    double* tmp;
    int size;
    int portion;
 public:
    QuickParallelSorter(double* _mas, double* _tmp, int _size,
        int _portion) : mas(_mas), tmp(_tmp),
        size(_size), portion(_portion)
    {}
    void operator()();
};

void ParallelSort(double* inp, int size,
    int nThreads);

void StdQuickSort(double* arr, int left, int right);
void quickSort(int left, int right, std::vector <double>* arr);
void getRandomArray(double * arr, int size);
bool checkCorrectnessOfSort(double* arr, int size);
#endif  // MODULES_TASK_4_KOROBEINIKOV_A_QUICK_SORT_QUICK_SORT_H_
