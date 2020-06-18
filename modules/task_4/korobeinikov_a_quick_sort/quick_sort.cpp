// Copyright 2020 Korobeinikov Aleksei
#include <limits.h>
#include <thread>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include "../../modules/task_4/korobeinikov_a_quick_sort/quick_sort.h"


void EvenSplitter::operator()() {
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
    return;
}

void OddSplitter::operator()() {
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
    return;
}

void SimpleComparator::operator()(int start, int end) const {
    for (int i = start; i < end; i += 4)
        if (mas[i + 1] < mas[i]) {
            double _tmp = mas[i];
            mas[i] = mas[i + 1];
            mas[i + 1] = _tmp;
        }
}

void QuickParallelSorter::operator()() {
    if (size <= portion) {
        StdQuickSort(mas, 0, size - 1);
    } else {
        int s = size / 2 + (size / 2) % 2;
        std::thread left(*new QuickParallelSorter(mas, tmp, s, portion));
        std::thread right(*new QuickParallelSorter(mas + s, tmp + s, size - s, portion));
        left.join();
        right.join();
        // std::cout << s << " " << size - s << '\n';
        std::thread evenSplitter(*new EvenSplitter(mas, tmp, s, size - s));
        std::thread oddSplitter(*new OddSplitter(mas, tmp, s, size - s));
        evenSplitter.join();
        oddSplitter.join();
        std::thread CompFirst(*new SimpleComparator(mas), 1, size - 1);
        std::thread CompSecond(*new SimpleComparator(mas), 3, size - 1);
        CompFirst.join();
        CompSecond.join();
    }
    return;
}

void ParallelSort(double* inp, int size, int nThreads) {
    double* tmp = new double[size];
    int portion = size / nThreads;
    if (size % nThreads != 0)
        portion++;
    // std::cout << portion << '\n';
    std::thread boss(*new QuickParallelSorter(inp, tmp, size, portion));
    boss.join();
    delete[] tmp;
}


void StdQuickSort(double* arr, int left, int right) {
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
            StdQuickSort(arr, it_l, right);
            right = it_l - 1;
        } else {
            StdQuickSort(arr, left, it_l - 1);
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
