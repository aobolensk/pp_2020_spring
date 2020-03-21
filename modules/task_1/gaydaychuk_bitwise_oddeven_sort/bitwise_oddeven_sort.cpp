// Copyright 2020 Gaydaychuk Yury
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "../../../modules/task_1/gaydaychuk_bitwise_oddeven_sort/bitwise_oddeven_sort.h"

bool checkAscending(std::vector<int> vec) {
    return std::is_sorted(std::begin(vec), std::end(vec));
}

int getMax(std::vector<int> *vec) {
    int n = vec->size();
    int max = vec->at(0);
    for (int i = 1; i < n; i++) {
        if (vec->at(i) > max) {
            max = vec->at(i);
        }
    }
    return max;
}

void sortByDigit(std::vector<int> *vec, int digit) {
    int n = vec->size();
    std::vector<int> res(n);
    int i, count[10] = {0};
    for (i = 0; i < n; i++) {
        count[(vec->at(i) / digit) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (i = n - 1; i >= 0; i--) {
        res[count[(vec->at(i) / digit) % 10] - 1] = vec->at(i);
        count[(vec->at(i) / digit) % 10]--;
    }
    for (i = 0; i < n; i++) {
        vec->at(i) = res[i];
    }
}

void bitwiseSort(std::vector<int> *vec) {
    int max = getMax(vec);
    for (int digit = 1; max / digit > 0; digit *= 10)
        sortByDigit(vec, digit);
}
