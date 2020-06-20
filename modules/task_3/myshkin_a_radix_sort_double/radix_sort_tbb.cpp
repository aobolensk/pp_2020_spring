// Copyright 2020 Myshkin Andrey
#include "../../../modules/task_3/myshkin_a_radix_sort_double/radix_sort_tbb.h"

#include <tbb/task_group.h>
#include <tbb/tbb.h>
#include "tbb/parallel_sort.h"

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

class Counter : public tbb::task {
    double* buffer;
    int length;
    int* counter;
    int valbyte;

 public:
     Counter(double* buffer_, int length_, int* counter_, int valbyte_) :
         buffer(buffer_), length(length_), counter(counter_), valbyte(valbyte_)
     {}

     task* execute() {
         unsigned char *buf = (unsigned char *)buffer;
         memset(counter, 0, sizeof(int) * 256);

         for (int i = 0; i < length; i++)
             counter[buf[8 * i + valbyte]]++;

         return NULL;
     }
};

class Deployment : public tbb::task {
    double* input;
    double* output;
    int length;
    int* counter;
    int valbyte;

 public:
     Deployment(double* input_, double* output_, int length_, int* counter_, int valbyte_) :
         input(input_), output(output_), length(length_), counter(counter_), valbyte(valbyte_)
     {}

     task* execute() {
         unsigned char *buf = (unsigned char *)input;
         for (int i = 0; i < length; i++) {
             output[counter[buf[8 * i + valbyte]]] = input[i];
             counter[buf[8 * i + valbyte]]++;
         }

         return NULL;
     }
};

class CountingSort : public tbb::task {
    double* buffer;
    double* buf;
    int length;
    int* counters;
    int valbyte;
    int NumThreads;

 public:
    CountingSort(double* buffer_, double* buf_, int length_,
        int* counters_, int valbyte_, int NumThreads_) :
        buffer(buffer_), buf(buf_), length(length_),
        counters(counters_), valbyte(valbyte_), NumThreads(NumThreads_)
    {}

    task* execute() {
        int n = NumThreads - 1;
        Counter** bufCount = new Counter*[n];
        Deployment** bufDep = new Deployment*[n];

        int delta = length / NumThreads;

        for (int i = 0; i < n; i++) {
            bufCount[i] = new (allocate_child())
                Counter(buffer + i * delta, delta, counters + i * 256, valbyte);
        }
        Counter& lastCount = *new (allocate_child())
            Counter(buffer + n * delta, length - n * delta,
                counters + n * 256, valbyte);

        set_ref_count(NumThreads + 1);

        for (int i = 0; i < n; i++)
            spawn(*(bufCount[i]));

        spawn_and_wait_for_all(lastCount);

        int value = 0;
        for (int j = 0; j < 256; j++) {
            for (int i = 0; i < NumThreads; i++) {
                int tmp = counters[j + i * 256];
                counters[j + i * 256] = value;
                value += tmp;
            }
        }

        for (int i = 0; i < n; i++) {
            bufDep[i] = new (allocate_child())
                Deployment(buffer + i * delta, buf, delta,
                    counters + i * 256, valbyte);
        }
        Deployment& lastDep = *new (allocate_child())
            Deployment(buffer + delta * n, buf,
                length - delta * n, counters + n * 256, valbyte);

        set_ref_count(NumThreads + 1);

        for (int i = 0; i < n; i++)
            spawn(*(bufDep[i]));

        spawn_and_wait_for_all(lastDep);

        delete[] bufCount;
        delete[] bufDep;

        return NULL;
    }
};

class RadixSortUnsigned : public tbb::task {
    double* buffer;
    double* buf;
    int length;
    int NumThreads;

 public:
    RadixSortUnsigned(double* buffer_, double* buf_, int length_, int NumThreads_) :
        buffer(buffer_), buf(buf_), length(length_), NumThreads(NumThreads_)
    {}

    task* execute() {
        int* counters = new int[256 * NumThreads];
        CountingSort* tmp = nullptr;

        for (int i = 0; i < 4; i++) {
            tmp = new (allocate_child())
                CountingSort(buffer, buf, length, counters, 2 * i, NumThreads);
            set_ref_count(2);
            spawn_and_wait_for_all(*tmp);

            tmp = new (allocate_child())
                CountingSort(buf, buffer, length, counters, 2 * i + 1, NumThreads);
            set_ref_count(2);
            spawn_and_wait_for_all(*tmp);
        }

        delete[] counters;

        return NULL;
    }
};

int RadixSort(double* buffer, int length, int NumThreads) {
    if (length < 1) { return -1; }
    // printf(" Not positive array size(%d)\n", length);
    if (buffer == nullptr) { printf(" Not positive array size(buffer)\n"); return -1; }
    double* tmp = nullptr;
    double* posArray = nullptr;
    double* negArray = nullptr;
    int poslen = 0, neglen = 0;
    int sts = 0;

    tbb::task_scheduler_init init(NumThreads);

    posArray = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    if (posArray == nullptr) { printf(" Unable to allocate memory for an array(posArray)\n"); return -1; }
    negArray = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    if (negArray == nullptr) { printf(" Unable to allocate memory for an array(negArray)\n"); return -1; }
    tmp = reinterpret_cast<double*>(malloc(sizeof(double) * length));
    if (tmp == nullptr) { return -1; }

    for (int i = 0; i < length; i++) {
        if (buffer[i] >= 0) {
            posArray[poslen] = buffer[i]; poslen++;
        } else { negArray[neglen] = buffer[i]; neglen++; }
    }

    RadixSortUnsigned& sorter1 = *new (tbb::task::allocate_root())
        RadixSortUnsigned(posArray, tmp, poslen, NumThreads);
    tbb::task::spawn_root_and_wait(sorter1);

    RadixSortUnsigned& sorter2 = *new (tbb::task::allocate_root())
        RadixSortUnsigned(negArray, tmp, neglen, NumThreads);
    tbb::task::spawn_root_and_wait(sorter2);

    sts = MergeArrays(negArray, neglen, posArray, poslen, buffer);

    if (tmp) { free(tmp); tmp = nullptr; }
    if (posArray) { free(posArray); posArray = nullptr; }
    if (negArray) { free(negArray); negArray = nullptr; }

    init.terminate();
    return sts;
}
