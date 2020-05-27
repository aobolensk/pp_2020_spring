// Copyright 2020 Myshkin Andrey
#include "../../../modules/task_1/myshkin_a_radix_sort_double/radix_sort_double.h"
#include <stdio.h>
#include <cstring>
#include <utility>


int getRandomArray(double* buffer, int length, double rangebot, double rangetop) {
    if ((length <= 0) || (buffer == nullptr)) return -1;
    if (rangebot >= rangetop) return -1;
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<double> buf(rangebot, rangetop);
    for (int i = 0; i < length; i++) {
        buffer[i] = buf(gen);
    }
    return 0;
}

int MergeArrays(double* buffer1, int length1, double *buffer2, int length2, double *result) {
    if ((length1 < 0) || (length2 < 0)) return -1;
    if ((buffer1 == nullptr) || (buffer2 == nullptr) || (result == nullptr)) return -1;
    int k = 0;
    for (int i = length1 - 1; i >= 0; i--) {
        result[k] = buffer1[i];
        k++;
    }
    for (int j = 0; j < length2; j++) {
        result[k] = buffer2[j];
        k++;
    }

    return 0;
}

int SortingCheck(double *buffer, int length) {
    if (length < 1) return -1;
    if (buffer == nullptr) return -1;

    for (int i = 0; i < length - 1; i++) {
        if (buffer[i] <= buffer[i + 1]) {
            i++;
        } else {
            return -1;
        }
    }
    return 0;
}

void CountingSort(double *input, double *output, int valbyte, int length) {
    unsigned char *buffer = (unsigned char *)input;
    // int amount = pow(2, sizeof(double));
    // int *counter = (int*)malloc(sizeof(int) * amount); // amount = 256
    int counter[256];
    int value;
    memset(counter, 0, sizeof(int) * 256);

    for (int i = 0; i < length; i++)
        counter[buffer[8 * i + valbyte]]++;

    int j;
    for (j = 0; j < 256; j++) {
        if (counter[j] != 0) break;
    }

    value = counter[j];
    counter[j] = 0;
    j++;
    for (; j < 256; j++) {
        int tmp = counter[j];
        counter[j] = value;
        value += tmp;
    }

    for (int i = 0; i < length; i++) {
        output[counter[buffer[8 * i + valbyte]]] = input[i];
        counter[buffer[8 * i + valbyte]]++;
    }

    // if (counter) { free(counter); counter = NULL; }
}

int RadixSortUnsigned(double *buffer, int length) {
    if (length < 1) { return 0; }
    if (length < 0) { return -1; }
    if (buffer == nullptr) { printf("Not found items in array!\n"); return -1; }
    double *outbuf = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    if (outbuf == nullptr) { printf("Unable to allocate memory for array!\n"); return -1; }

    for (int i = 0; i < 4; i++) {
        CountingSort(buffer, outbuf, 2 * i, length);
        CountingSort(outbuf, buffer, 2 * i + 1, length);
    }

    if (outbuf) { free(outbuf); outbuf = nullptr; }

    return 0;
}


int RadixSort(double* buffer, int length) {
    if (length < 1) return -1;
    if (buffer == nullptr) return -1;
    double* posArray = nullptr;
    double* negArray = nullptr;
    int poslen = 0, neglen = 0;
    int sts = 0;

    posArray = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    if (posArray == nullptr) { return -1; }
    negArray = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    if (negArray == nullptr) { return -1; }

    for (int i = 0; i < length; i++) {
        if (buffer[i] >= 0) { posArray[poslen] = buffer[i]; poslen++;
        } else { negArray[neglen] = buffer[i]; neglen++; }
    }

    sts = RadixSortUnsigned(negArray, neglen);
    sts = RadixSortUnsigned(posArray, poslen);

    sts = MergeArrays(negArray, neglen, posArray, poslen, buffer);

    if (posArray) { free(posArray); posArray = nullptr; }
    if (negArray) { free(negArray); negArray = nullptr; }

    return sts;
}
