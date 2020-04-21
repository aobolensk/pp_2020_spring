// Copyright 2020 Repin Vladimir

#include <tbb/tbb.h>
#include <random>
#include <vector>
#include <ctime>
#include <queue>
#include <stack>
#include <utility>

#include "../../../modules/task_3/repin_v_radix_sort_oddeven_merge_double/radix_sort.h"

std::vector<double> GetRandomVector(int size) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<double> dist(-1000.0, 1000.0);
    std::vector <double> vec(size);
    for (int i = 0; i < size; i++) { vec[i] = dist(gen); }
    return vec;
}

void SortByByte(double *inp, double *out, int offset, int size) {
    unsigned char *mas = (unsigned char *)inp;
    int counter[256];
    int temp;
    memset(counter, 0, sizeof(counter[0]) * 256);

    for (int i = 0; i < size; i++)
        counter[mas[8 * i + offset]]++;

    if (offset != 7) {
        int j = 0;
        for (; j < 256; j++) {
            if (counter[j] != 0)
                break;
        }
        temp = counter[j];
        counter[j] = 0;
        j++;
        for (; j < 256; j++) {
            int b = counter[j];
            counter[j] = temp;
            temp += b;
        }
        for (int i = 0; i < size; i++) {
            out[counter[mas[8 * i + offset]]] = inp[i];
            counter[mas[8 * i + offset]]++;
        }
    } else {
        int j = 255;
        for (; j >= 128; j--)
            if (counter[j] != 0)
                break;


        temp = counter[j] - 1;
        counter[j] = temp;

        if (j != 128) {
            j--;
            for (; j >= 128; j--) {
                int b = counter[j];
                temp += b;
                counter[j] = temp;
            }
        }

        temp++;

        j = 0;
        for (; j < 128; j++) {
            if (counter[j] != 0)
                break;
        }

        for (; j < 128; j++) {
            int b = counter[j];
            counter[j] = temp;
            temp += b;
        }

        for (int i = 0; i < size; i++) {
            int cur_byte = mas[8 * i + offset];
            out[counter[cur_byte]] = inp[i];
            if (cur_byte < 128)
                counter[cur_byte]++;
            else
                counter[cur_byte]--;
        }
    }
}

void RadixSortDouble(double *inp, double *out, int size) {
    for (int i = 0; i < 8; i += 2) {
        SortByByte(inp, out, i, size);
        SortByByte(out, inp, i + 1, size);
    }
}

void Merge(double *inp, double *temp, int mid, int size, int even) {
    for (int i = even; i < mid; i += 2)
        temp[i] = inp[i];
    double *inp2 = inp + mid;
    int a = even;
    int b = even;
    int i = even;
    while ((a < mid) && (b < size)) {
        if (temp[a] <= inp2[b]) {
            inp[i] = temp[a];
            a += 2;
        } else {
            inp[i] = inp2[b];
            b += 2;
        }
        i += 2;
    }
    if (a == mid) {
        for (int j = b; j < size; j += 2, i += 2)
            inp[i] = inp2[j];
    } else {
        for (int j = a; j < mid; j += 2, i += 2)
            inp[i] = temp[j];
    }
}

void OddEvenMergeSortTBB(double *inp, int size, int portion, int numthreads) {
    tbb::task_scheduler_init init(numthreads);
    double* temp = new double[size];
    std::queue<std::pair<int, int>> current_layer, next_layer;
    std::stack<std::pair<int, std::pair<int, int>>> merge_order;
    std::vector<std::pair<int, int>> parts;

    std::pair<int, int> cur;

    current_layer.push({ 0, size });
    merge_order.push({ 0, {0, 0} });

    bool divided = false;
    while (!divided) {
        cur = current_layer.front();
        current_layer.pop();
        if (cur.second > portion) {
            int mid = cur.second / 2 + (cur.second / 2) % 2;
            merge_order.push({ cur.first, {mid, cur.second - mid} });;
            next_layer.push({ cur.first, mid });
            next_layer.push({ cur.first + mid, cur.second - mid});
        } else {
            parts.push_back(cur);
        }
        if (current_layer.empty()) {
            if (next_layer.empty()) {
                divided = true;
            } else {
                current_layer = next_layer;
                next_layer = std::queue<std::pair<int, int>>();
                merge_order.push({ 0, { 0, 0 } });
            }
        }
    }
    merge_order.pop();
    tbb_radix body1(inp, temp, parts);
    tbb::parallel_for(tbb::blocked_range<int>(0, parts.size(), 1), body1);

    std::vector<std::pair<int, std::pair<int, int>>> current_order;

    while (!merge_order.empty()) {
        while (merge_order.top().second.second != 0) {
            current_order.push_back(merge_order.top());
            merge_order.pop();
        }
        merge_order.pop();

        tbb_merge body2(inp, temp, current_order);
        tbb::parallel_for(tbb::blocked_range<int>(0,
            current_order.size() * 2, 1), body2);

        tbb_shuffle body3(inp, temp, current_order);
        tbb::parallel_for(tbb::blocked_range<int>(0,
            current_order.size() , 1), body3);

        current_order.clear();
    }
    delete[] temp;
}
