// Copyright 2020 Korobeinikov Aleksei
#include <omp.h>
#include <limits.h>
#include <tbb/tbb.h>
#include <tbb/task.h>
#include <tbb/blocked_range.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <utility>
#include "../../modules/task_3/korobeinikov_a_quick_sort/quick_sort.h"


tbb::task* EvenSplitter::execute() {
    for (int i = 0; i < size1; i += 2)
        tmp[i] = mas[i];
    double* mas2 = mas + size1;
    int a = 0;
    int b = 0;
    int i = 0;
    while ((a < size1) && (b < size2)) {
        if (tmp[a] <= mas2[b]) {
            mas[i] = tmp[a];
            a += 2;
        } else {
            mas[i] = mas2[b];
            b += 2;
        }
        i += 2;
    }
    if (a == size1) {
        for (int j = b; j < size2; j += 2, i += 2)
            mas[i] = mas2[j];
    } else {
        for (int j = a; j < size1; j += 2, i += 2)
            mas[i] = tmp[j];
    }
    return NULL;
}
tbb::task* OddSplitter::execute() {
    for (int i = 1; i < size1; i += 2)
        tmp[i] = mas[i];
    double* mas2 = mas + size1;
    int a = 1;
    int b = 1;
    int i = 1;
    while ((a < size1) && (b < size2)) {
        if (tmp[a] <= mas2[b]) {
            mas[i] = tmp[a];
            a += 2;
        } else {
            mas[i] = mas2[b];
            b += 2;
        }
        i += 2;
    }
    if (a == size1) {
        for (int j = b; j < size2; j += 2, i += 2)
            mas[i] = mas2[j];
    } else {
        for (int j = a; j < size1; j += 2, i += 2)
            mas[i] = tmp[j];
    }
    return NULL;
}

void SimpleComparator::operator()(const tbb::blocked_range<int>& r) const {
    int begin = r.begin(), end = r.end();
    for (int i = begin; i < end; i++)
        if (mas[2 * i] < mas[2 * i - 1]) {
            double _tmp = mas[2 * i - 1];
            mas[2 * i - 1] = mas[2 * i];
            mas[2 * i] = _tmp;
        }
}

tbb::task* QuickParallelSorter::execute() {
    if (size <= portion) {
        TbbQuickSort(mas, 0, size - 1);
    } else {
        int s = size / 2 + (size / 2) % 2;
        QuickParallelSorter& sorter1 = *new(allocate_child())
            QuickParallelSorter(mas, tmp, s, portion);
        QuickParallelSorter& sorter2 = *new(allocate_child())
            QuickParallelSorter(mas + s, tmp + s, size - s,
                portion);
        set_ref_count(3);
        spawn(sorter1);
        spawn_and_wait_for_all(sorter2);
        // std::cout << s << " " << size - s << '\n';
        EvenSplitter& splitter1 = *new(allocate_child()) EvenSplitter(mas, tmp, s, size - s);
        OddSplitter& splitter2 = *new(allocate_child()) OddSplitter(mas, tmp, s, size - s);
        set_ref_count(3);
        spawn(splitter1);
        spawn_and_wait_for_all(splitter2);

        tbb::parallel_for(tbb::blocked_range<int>(1, (size + 1) / 2),
            SimpleComparator(mas));
    }
    return NULL;
}
void TbbParallelSort(double* inp, int size, int nThreads) {
    double* tmp = new double[size];
    int portion = size / nThreads;
    if (size % nThreads != 0)
        portion++;
    // std::cout << portion << '\n';
    QuickParallelSorter& sorter = *new(tbb::task::allocate_root())
        QuickParallelSorter(inp, tmp, size, portion);
    tbb::task::spawn_root_and_wait(sorter);
    delete[] tmp;
}

void TbbQuickSort(double* arr, int left, int right) {
    while (right > left) {
        int it_l = left;
        int it_r = right;
        double pivot = arr[(left + right) / 2];
        // partition
        while (it_l <= it_r) {
            while (arr[it_l] < pivot) {
                it_l++;
            }
            while (arr[it_r] > pivot) {
                it_r--;
            }
            if (it_l <= it_r) {
                std::swap(arr[it_l], arr[it_r]);
                it_l++;
                it_r--;
            }
        }
        // recursion
        if (2 * it_l > left + right) {
            TbbQuickSort(arr, it_l, right);
            right = it_l - 1;
        } else {
            TbbQuickSort(arr, left, it_l - 1);
            left = it_l;
        }
    }
    return;
}


void getRandomArray(double* arr, int size) {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution <int> dist(-1000, 1000);
    for (int i = 0; i < size; ++i) {
        arr[i] = dist(gen);
    }
    return;
}


bool checkCorrectnessOfSort(double* arr, int size) {
    return std::is_sorted(arr, arr + size);
}
