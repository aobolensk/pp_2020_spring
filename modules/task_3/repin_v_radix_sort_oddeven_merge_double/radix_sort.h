// Copyright 2020 Repin Vladimir
#ifndef MODULES_TASK_3_REPIN_V_RADIX_SORT_ODDEVEN_MERGE_DOUBLE_RADIX_SORT_H_
#define MODULES_TASK_3_REPIN_V_RADIX_SORT_ODDEVEN_MERGE_DOUBLE_RADIX_SORT_H_

#include <tbb/tbb.h>
#include <random>
#include <vector>
#include <ctime>
#include <utility>
#include <cstring>

std::vector<double> GetRandomVector(int size);
void SortByByte(double *inp, double *out, int byteNum, int size);
void RadixSortDouble(double *inp, double *out, int size);
void Merge(double *inp, double *temp, int mid, int size, int even);
void OddEvenMergeSortTBB(double *inp, int size, int portion, int numthreads);

class tbb_radix {
 private:
    double *inp;
    double *temp;
    std::vector<std::pair<int, int>> parts;

 public:
    tbb_radix(double *inp_, double *temp_,
        const std::vector<std::pair<int, int>>& parts_) {
        inp = inp_;
        temp = temp_;
        parts = parts_;
    }
    void operator() (const tbb::blocked_range<int> &range) const {
        RadixSortDouble(inp + parts[range.begin()].first,
            temp + parts[range.begin()].first, parts[range.begin()].second);
    }
};

class tbb_merge {
 private:
    double *inp;
    double *temp;
    std::vector<std::pair<int, std::pair<int, int>>> current_order;

 public:
    tbb_merge(double *inp_, double *temp_,
        const std::vector<std::pair<int, std::pair<int, int>>>& cur_ord) {
        inp = inp_;
        temp = temp_;
        current_order = cur_ord;
    }
    void operator() (const tbb::blocked_range<int> &range) const {
        int i = range.begin();
        int st = current_order[i / 2].first;
        int s1 = current_order[i / 2].second.first;
        int s2 = current_order[i / 2].second.second;
        Merge(inp + st, temp + st, s1, s2, i % 2);
    }
};

class tbb_shuffle {
 private:
    double *inp;
    double *temp;
    std::vector<std::pair<int, std::pair<int, int>>> current_order;

 public:
    tbb_shuffle(double *inp_, double *temp_,
        const std::vector<std::pair<int, std::pair<int, int>>>& cur_ord) {
        inp = inp_;
        temp = temp_;
        current_order = cur_ord;
    }
    void operator() (const tbb::blocked_range<int> &range) const {
        int i = range.begin();
        int st = current_order[i].first;
        int s1 = current_order[i].second.first;
        int s2 = current_order[i].second.second;

        for (int j = 1; j < (s1 + s2 + 1) / 2; j++)
            if (inp[st + 2 * j] < inp[st + 2 * j - 1]) {
                double tmp = inp[st + 2 * j - 1];
                inp[st + 2 * j - 1] = inp[st + 2 * j];
                inp[st + 2 * j] = tmp;
            }
    }
};

#endif  // MODULES_TASK_3_REPIN_V_RADIX_SORT_ODDEVEN_MERGE_DOUBLE_RADIX_SORT_H_
