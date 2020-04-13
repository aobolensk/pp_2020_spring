// Copyright 2020 Repin Vladimir

#include <random>
#include <vector>
#include <ctime>
#include <cstring>
#include "../../../modules/task_1/repin_v_radix_sort_oddeven_merge_double/radix_sort.h"

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

void OddEvenMergeSort(double *inp, double *temp, int size, int portion) {
    if (size <= portion) {
        RadixSortDouble(inp, temp, size);
    } else {
        int mid = size / 2 + (size / 2) % 2;
        OddEvenMergeSort(inp, temp, mid, portion);
        OddEvenMergeSort(inp + mid, temp + mid, size - mid, portion);
        Merge(inp, temp, mid, size - mid, 0);
        Merge(inp, temp, mid, size - mid, 1);
        for (int i = 1; i < (size + 1) / 2; i++)
            if (inp[2 * i] < inp[2 * i - 1]) {
                double tmp = inp[2 * i - 1];
                inp[2 * i - 1] = inp[2 * i];
                inp[2 * i] = tmp;
            }
    }
}
