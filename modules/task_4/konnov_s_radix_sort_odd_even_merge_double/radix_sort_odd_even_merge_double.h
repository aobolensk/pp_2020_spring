// Copyright 2020 Konnov Sergey

#ifndef MODULES_TASK_4_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_
#define MODULES_TASK_4_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_

#include <omp.h>
#include <vector>
#include <queue>
#include <utility>
#include <iostream>

class task {
 public:
    std::vector<task*> ref;
    int num_of_depends;
    virtual void execute() = 0;
    virtual void print() = 0;
    virtual ~task(){}
};

class sortTask: public task {
    double * array;
    int index, size;
    std::vector<double> ans;
 public:
    sortTask(double* array, int index, int size);
    void execute() override;
    void print() override {
        std::cout << "sort " << index << " " << size << "\n";
    }
    virtual ~sortTask(){}
};

class oddEvenTask: public task {
    double * array;
    int index, size;
 public:
    oddEvenTask(double * array, int index, int size);
    void execute() override;
    void print() override {
        std::cout << "oddEvenMerge " << index << " " << size << "\n";
    }
    virtual ~oddEvenTask(){}
};

class oddTask: public task {
    double * array;
    int index1, size1, index2, size2;
 public:
    oddTask(double * array, int index1, int size1, int index2, int size2);
    void execute() override;
    void print() override {
        std::cout << "oddMerge " << index1 << " " << size1 << " " << index2 << " " << size2 << "\n";
    }
    virtual ~oddTask(){}
};

class evenTask: public task {
    double * array;
    int index1, size1, index2, size2;
 public:
    evenTask(double * array, int index1, int size1, int index2, int size2);
    void execute() override;
    void print() override {
        std::cout << "evenMerge " << index1 << " " << size1 << " " << index2 << " " << size2 << "\n";
    }
    virtual ~evenTask(){}
};

void gen_tasks(double* array, int left, int right, const std::vector<task*>& tasks,
                            const std::vector<int>& portion, task* queue[], bool is_begin = false);
std::vector<double> getRandomVector(int size, double lower_bound, double upper_bound, int seed = -1);
void countingSort(double* array, int size, int byteNum);
void radixSortOddEvenMergeDouble(double* array, int index, int size);
void oddMerge(double* array, int index1, int size1, int index2, int size2);
void evenMerge(double* array, int index1, int size1, int index2, int size2);
void oddEvenMerge(double* array, int index, int size);
std::vector<double> getRandomVector(int size, double lower_bound, double upper_bound, int seed);
std::vector<double> radixSortOddEvenMergeDoubleParallel(const std::vector<double>& v, int num_threads);

#endif  // MODULES_TASK_4_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_
