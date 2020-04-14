// Copyright 2020 Korobeinikov Aleksei
#include <omp.h>
#include <limits.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <utility>
#include "../../modules/task_2/korobeinikov_a_quick_sort/quick_sort.h"

const int inf = INT_MAX;

void EvenSplitter(int start, size_t size1, size_t size2,
    std::vector <double>* arr) {
    std::vector <double> tmp(size1);
    for (size_t i = 0; i < size1; i += 2) {
        tmp[i] = arr->at(start + i);
    }
    size2 = start + size1 + size2;
    size_t first_iter = 0;
    size_t second_iter = start + size1;
    size_t common_iter = start;
    while (first_iter < size1 && second_iter < size2) {
        if (tmp[first_iter] < arr->at(second_iter)) {
            arr->at(common_iter) = tmp[first_iter];
            first_iter += 2;
        } else {
            arr->at(common_iter) = arr->at(second_iter);
            second_iter += 2;
        }
        common_iter += 2;
    }
    if (first_iter >= size1) {
        for (size_t i = second_iter; i < size2; i += 2, common_iter += 2) {
            arr->at(common_iter) = arr->at(i);
        }
    } else {
        for (size_t i = first_iter; i < size1; i += 2, common_iter += 2) {
            arr->at(common_iter) = tmp[i];
        }
    }
}

void OddSplitter(int start, size_t size1, size_t size2,
    std::vector <double>* arr) {
    std::vector <double> tmp(size1);
    for (size_t i = 1; i < size1; i += 2) {
        tmp[i] = arr->at(start + i);
    }
    size2 = start + size1 + size2;
    size_t first_iter = 1;
    size_t second_iter = start + size1 + 1;
    size_t common_iter = start + 1;
    while (first_iter  < size1 && second_iter < size2) {
        if (tmp[first_iter] < arr->at(second_iter)) {
            arr->at(common_iter) = tmp[first_iter];
            first_iter += 2;
        } else {
            arr->at(common_iter) = arr->at(second_iter);
            second_iter += 2;
        }
        common_iter += 2;
    }
    if (first_iter >= size1) {
        for (size_t i = second_iter; i < size2; i += 2, common_iter += 2) {
                arr->at(common_iter) = arr->at(i);
        }
    } else {
        for (size_t i = first_iter; i < size1; i += 2, common_iter += 2) {
                arr->at(common_iter) = tmp[i];
        }
    }
}

void quickSortParallel(std::vector <double>* arr, int p) {
    int n = arr->size();
    int num = p;
    omp_set_num_threads(num);
    int tmp = n / num;
    int a = tmp + tmp % 2;
    int tmp2 = n - (num - 1) * a;
    int b = tmp2 + tmp2 % 2;
    int delta = (num - 1) * a + b - n;
    for (int i = 0; i < delta; ++i) {
        arr->push_back(inf);
    }
#pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < num; ++i) {
            int left = i * a;
            int right = (i + 1 == num) ? n + delta - 1 : left + a - 1;
            quickSort(left, right, arr);
        }
    }
    int count_m = num / 2;
    int k = 1;
    int last = 0;
    while (count_m > 0) {
#pragma omp parallel
        {
            int thread = omp_get_thread_num();
            if (thread < 2 * count_m) {
                if (thread % 2 == 0) {
                    EvenSplitter(thread * a * k, a * k,
                        (thread  == num - 2? a * last + b : a * k), arr);
                } else {
                    OddSplitter((thread - 1) * a * k, a * k,
                        (thread == num - 1 ? a * last + b : a * k), arr);
                }
            }
        }
#pragma omp parallel
        {
            int thread = omp_get_thread_num();
            if (thread < 2 * count_m) {
                if (thread % 2 == 0) {
                    int start = thread * a * k + 1;
                    int fin = (thread + 1 == num - 1 ? arr->size() :
                        (thread + 2) * a * k);
                    for (int i = start; i < fin - 1; i += 4) {
                        if (arr->at(i) > arr->at(i + 1)) {
                            std::swap(arr->at(i), arr->at(i + 1));
                        }
                    }
                } else {
                    int start = (thread - 1) * a * k + 3;
                    int fin = (thread  == num - 1 ? arr->size() :
                        (thread + 1) * a * k);
                    for (int i = start; i < fin - 1; i += 4) {
                        if (arr->at(i) > arr->at(i + 1)) {
                            std::swap(arr->at(i), arr->at(i + 1));
                        }
                    }
                }
            }
        }
        if (num % 2 == 0) {
            last += k;
        }
        num -= count_m;
        count_m = num / 2;
        k *= 2;
    }
    for (int i = 0; i < delta; ++i) {
        arr->pop_back();
    }
}

void quickSort(int left, int right, std::vector <double>* arr) {
    while (right > left) {
        int it_l = left;
        int it_r = right;
        double pivot = arr -> at((left + right) / 2);
        // partition
        while (it_l <= it_r) {
            while (arr -> at(it_l) < pivot) {
                it_l++;
            }
            while (arr -> at(it_r) > pivot) {
                it_r--;
            }
            if (it_l <= it_r) {
                std::swap(arr -> at(it_l), arr -> at(it_r));
                it_l++;
                it_r--;
            }
        }
        // recursion
        if (2 * it_l > left + right) {
            quickSort(it_l, right, arr);
            right = it_l - 1;
        } else {
            quickSort(left, it_l - 1, arr);
            left = it_l;
        }
    }
    return;
}

std::vector <double> getRandomVector(int size) {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution <int> dist(-1000, 1000);
    std::vector <double> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = dist(gen);
    }
    return vec;
}

bool checkCorrectnessOfSort(std::vector <double>* vec) {
    return std::is_sorted((*vec).begin(), (*vec).end());
}
