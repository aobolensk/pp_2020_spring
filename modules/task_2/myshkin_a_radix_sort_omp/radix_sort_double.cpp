// Copyright 2020 Myshkin Andrey
#include <omp.h>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <random>
#include <utility>
#include "../../../modules/task_2/myshkin_a_radix_sort_omp/radix_sort_double.h"

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

int ArrayComparison(double* buffer1, double *buffer2, int length) {
    if (length < 0) return -1;
    if ((buffer1 == nullptr) || (buffer2 == nullptr)) return -1;
    for (int i = 0; i < length; i++) {
        if (buffer1[i] == buffer2[i]) {
            i++;
        } else {
            return -1;
        }
    }

    return 0;
}

int MergeArraySigned(double* buffer1, int length1, double *buffer2, int length2, double *result) {
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
        if (buffer[i] >= 0) {
            posArray[poslen] = buffer[i]; poslen++;
        } else {
            negArray[neglen] = buffer[i]; neglen++;
        }
    }

    sts = RadixSortUnsigned(negArray, neglen);
    sts = RadixSortUnsigned(posArray, poslen);

    sts = MergeArraySigned(negArray, neglen, posArray, poslen, buffer);

    if (posArray) { free(posArray); posArray = nullptr; }
    if (negArray) { free(negArray); negArray = nullptr; }

    return sts;
}

int MergeArrayForOmp(double* buffer1, int length1, double* buffer2, int length2) {
    if ((buffer1 == nullptr) || (buffer2 == nullptr)) return -1;
    if ((length1 < 0) || (length2 < 0)) return -1;
    int i = 0, j = 0;
    int k = 0;
    int length = length1 + length2;
    double* result = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    if (result == nullptr) { printf("Error: No memory allocated"); }
    while (length1 && length2) {
        if (buffer1[i] < buffer2[j]) {
            result[k] = buffer1[i];
            i++;
            length1--;
        } else {
            result[k] = buffer2[j];
            j++;
            length2--;
        }
        k++;
    }

    if (length1 == 0) {
        for (int z = j; z < j + length2; z++) {
            result[k] = buffer2[z];
            k++;
        }
    } else if (length2 == 0) {
        for (int z = i; z < i + length1; z++) {
            result[k] = buffer1[z];
            k++;
        }
    }

    memcpy(buffer1, result, sizeof(double) * length);

    if (result) { free(result); result = nullptr; }
    return 0;
}

int RadixSortOmp(double* buffer, int length, int num_threads) {
    if (length < 1) return -1;
    if (buffer == nullptr) return -1;
    omp_set_num_threads(num_threads);
    double* posArray = nullptr;
    double* negArray = nullptr;
    double* bufferCpy = nullptr;
    double* tmpArr = nullptr;
    int poslen = 0, neglen = 0;
    int sts = 0;
    int flag = 0;
    int res, sizeThr;
    if (num_threads > length) num_threads = 4;

    bufferCpy = reinterpret_cast<double*>(malloc(sizeof(double) * length));

#pragma omp parallel shared(buffer, bufferCpy, flag) private(posArray, negArray, poslen, neglen, tmpArr, res, sizeThr)
    {
        int tid = omp_get_thread_num();
        poslen = 0, neglen = 0;
        sizeThr = length / num_threads;
        res = length % num_threads;

#pragma omp master
        sizeThr = sizeThr + res;
#pragma omp master
        res = 0;

        posArray = reinterpret_cast<double*>(malloc(sizeof(double) * sizeThr));
        memset(posArray, 0, sizeThr);
        if (posArray == nullptr) { printf("Error: No memory allocated"); }
        negArray = reinterpret_cast<double*>(malloc(sizeof(double) * sizeThr));
        memset(negArray, 0, sizeThr);
        if (negArray == nullptr) { printf("Error: No memory allocated"); }

        tmpArr = reinterpret_cast<double*>(malloc(sizeof(double) * sizeThr));
        memset(tmpArr, 0, sizeThr);
        if (tmpArr == nullptr) { printf("Error: No memory allocated"); }

        for (int j = 0; j < num_threads; j++) {
            if (tid == j) {
                for (int i = 0 + j * sizeThr; i < res + sizeThr * (j + 1); i++) {
                    if (buffer[i] >= 0) {
                        posArray[poslen] = buffer[i];
                        poslen++;
                    } else {
                        negArray[neglen] = buffer[i];
                        neglen++;
                    }
                }
            }
        }

#pragma omp barrier
        sts = RadixSortUnsigned(negArray, neglen);
        sts = RadixSortUnsigned(posArray, poslen);

        sts = MergeArraySigned(negArray, neglen, posArray, poslen, tmpArr);

#pragma omp master
        for (int i = 0; i < sizeThr; i++) {
            bufferCpy[i] = tmpArr[i];
        }
#pragma omp master
        flag++;
#pragma omp barrier
#pragma omp critical
        if (tid != 0) {
            sts = MergeArrayForOmp(bufferCpy, res + flag * sizeThr, tmpArr, sizeThr);
            flag++;
        }
    }

    memcpy(buffer, bufferCpy, sizeof(double) * length);

    if (posArray) { free(posArray); posArray = nullptr; }
    if (negArray) { free(negArray); negArray = nullptr; }
    if (tmpArr) { free(tmpArr); tmpArr = nullptr; }
    if (bufferCpy) { free(bufferCpy); bufferCpy = nullptr; }
    return sts;
}
