// Copyright 2020 Konnov Sergey

#ifndef MODULES_TASK_1_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_
#define MODULES_TASK_1_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_

#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <omp.h>
#include <iostream>
// std::vector<task&> tasks;
// std::queue<task&> queue;

class task {
public:
    std::vector<task*> ref;
    int num_of_depends;
    virtual void execute() = 0;
    virtual void print() = 0;
};

class sortTask: public task {
    double * array;
    int index, size;
    std::vector<double> ans;
public:
    sortTask(double* array, int index, int size);
    void execute() override;
    void print() {
        std::cout<<"sort "<<index<<" "<<size<<"\n";
    }
};

class oddEvenTask: public task {
    double * array;
    int index, size;
public:
    oddEvenTask(double * array, int index, int size);
    void execute() override;
    void print() {
        std::cout<<"oddEvenMerge "<<index<<" "<<size<<"\n";
    }
};

class oddTask: public task {
    double * array;
    int index1, size1, index2, size2;
public:
    oddTask(double * array, int index1, int size1, int index2, int size2);
    void execute() override;
    void print() {
        std::cout<<"oddMerge "<<index1<<" "<<size1<<" "<<index2<<" "<<size2<<"\n";
    }
};

class evenTask: public task {
    double * array;
    int index1, size1, index2, size2;
public:
    evenTask(double * array, int index1, int size1, int index2, int size2);
    void execute() override;
    void print() {
        std::cout<<"evenMerge "<<index1<<" "<<size1<<" "<<index2<<" "<<size2<<"\n";
    }
};

void gen_tasks(double* array, int left, int right, const std::vector<task*>& tasks, const std::vector<int>& portion, task* queue[], bool is_begin = false);

// std::vector<double> countingSort(std::vector<double> array, int byteNum);
// std::vector<double> radixSortOddEvenMergeDouble(const std::vector<double>& array);
std::vector<double> getRandomVector(int size, double lower_bound, double upper_bound, int seed = -1);
// void oddMerge(double * array, int index1, int size1, int index2, int size2);
// void evenMerge(double * array, int index1, int size1, int index2, int size2);
// void oddEvenMerge(double * array, int index, int size);
// int initialize(int num_threads, double* array, int size);

struct str {
    int ready_task, ready_merge, ready1, ready2;
    omp_lock_t lock, lock2, lock3, lock4;
};

void countingSort(double* array, int size, int byteNum);
int initialize(int num_threads, double * array, int size);
void radixSortOddEvenMergeDouble(double* array, int index, int size);
void oddMerge(double* array, int index1, int size1, int index2, int size2);
void evenMerge(double* array, int index1, int size1, int index2, int size2);
void oddEvenMerge(double* array, int index, int size);
std::vector<double> getRandomVector(int size, double lower_bound, double upper_bound, int seed);
void execute(double* array, int size, int left, int right, const std::vector<int>& portion, std::map<std::pair<int, int>, str>& m); 
std::vector<double> radixSortOddEvenMergeDoubleParallel(const std::vector<double>& v);

#endif  // MODULES_TASK_1_KONNOV_S_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_RADIX_SORT_ODD_EVEN_MERGE_DOUBLE_H_
