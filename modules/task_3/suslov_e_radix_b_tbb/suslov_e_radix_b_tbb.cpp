// Copyright 2020 Suslov Egor
#include <tbb/tbb.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <functional>
#include <numeric>
#include "../../../modules/task_3/suslov_e_radix_b_tbb/suslov_e_radix_b_tbb.h"

double* getRandomArray(int  size) {
    std::random_device rd;
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(rd()));
    double* Array = new double[size];
    for (int i = 0; i < size; i++) { Array[i] = (gen() % 100000) / 100.0 - 500.0; }
    return Array;
}

void CountingSortByte(double* inp, double* out, int byteNum, int size) {
    if (byteNum != 7) {
        unsigned char* mas = (unsigned char*)inp;
        int counter[256];
        int tem;
        memset(counter, 0, sizeof(int) * 256);
        for (int i = 0; i < size; i++)
            counter[mas[8 * i + byteNum]]++;
        int j = 0;
        for (; j < 256; j++) {
            if (counter[j] != 0)
                break;
        }
        tem = counter[j];
        counter[j] = 0;
        j++;
        for (; j < 256; j++) {
            int  sdvig = counter[j];
            counter[j] = tem;
            tem += sdvig;
        }
        for (int i = 0; i < size; i++) {
            out[counter[mas[8 * i + byteNum]]] = inp[i];
            counter[mas[8 * i + byteNum]]++;
        }
    } else {
        unsigned char* mas = (unsigned char*)inp;
        int counter[256];
        int tem = 0;
        memset(counter, 0, sizeof(int) * 256);
        for (int i = 0; i < size; i++)
            counter[mas[8 * i + byteNum]]++;
        int j = 255;
        for (; j >= 128; j--) {
            if (counter[j] != 0)
                break;
        }
        if (j != 127) {
            tem = counter[j] - 1;
            counter[j] = tem;
            j--;
            for (; j >= 128; j--) {
                int sdvig = counter[j];
                tem += sdvig;
                counter[j] = tem;
            }
        }
        tem++;
        j = 0;
        for (; j < 128; j++) {
            if (counter[j] != 0)
                break;
        }
        for (; j < 128; j++) {
            int sdvig = counter[j];
            counter[j] = tem;
            tem += sdvig;
        }
        for (int i = 0; i < size; i++) {
            out[counter[mas[8 * i + byteNum]]] = inp[i];
            if (mas[8 * i + byteNum] >= 128) {
                counter[mas[8 * i + byteNum]]--;
            } else {
                counter[mas[8 * i + byteNum]]++;
            }
        }
    }
}

void LSDSortDouble(double* inp, double* tmp, int size) {
    for (int i = 0; i < 7; i += 2) {
        CountingSortByte(inp, tmp, i, size);
        CountingSortByte(tmp, inp, i + 1, size);
    }
}

bool CompareArrays(double* mas, double* Mas, int size) {
    for (int i = 0; i < size; i++)
        if (mas[i] != Mas[i])
            return false;
    return true;
}

class EvenSplitter :public tbb::task {
 private:
    double* mas;
    double* tmp;
    int size1;
    int size2;

 public:
    EvenSplitter(double* _mas, double* _tmp, int _size1, int _size2) :
        mas(_mas), tmp(_tmp), size1(_size1), size2(_size2)
    {}
    task* execute() {
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
};

class OddSplitter :public tbb::task {
 private:
    double* mas;
    double* tmp;
    int size1;
    int size2;

 public:
    OddSplitter(double* _mas, double* _tmp, int _size1, int _size2) : mas(_mas), tmp(_tmp), size1(_size1), size2(_size2)
    {}
    task* execute() {
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
};

class SimpleComparator {
 private:
    double* mas;

 public:
    int size;
    SimpleComparator(double* _mas, int _size) : mas(_mas), size(_size)
    {}
    void operator()(const tbb::blocked_range<int>& r) const {
        int begin = r.begin(), end = r.end();
        for (int i = begin; i < end; i++)
            if (mas[2 * i] < mas[2 * i - 1]) {
                double _tmp = mas[2 * i - 1];
                mas[2 * i - 1] = mas[2 * i];
                mas[2 * i] = _tmp;
            }
    }
};

class LSDParallelSorter :public tbb::task {
 private:
    double* mas;
    double* tmp;
    int size;
    int portion;

 public:
    LSDParallelSorter(double* _mas, double* _tmp, int _size, int _portion) :
        mas(_mas), tmp(_tmp), size(_size), portion(_portion)
    {}
    task* execute() {
        if (size <= portion) {
            LSDSortDouble(mas, tmp, size);
        } else {
            int s = size / 2 + (size / 2) % 2;
            LSDParallelSorter& sorter1 = *new (allocate_child())
                LSDParallelSorter(mas, tmp, s, portion);
            LSDParallelSorter& sorter2 = *new (allocate_child())
                LSDParallelSorter(mas + s, tmp + s, size - s,
                    portion);
            set_ref_count(3);
            spawn(sorter1);
            spawn_and_wait_for_all(sorter2);
            EvenSplitter& splitter1 = *new (allocate_child())
                EvenSplitter(mas, tmp, s, size - s);
            OddSplitter& splitter2 = *new (allocate_child())
                OddSplitter(mas, tmp, s, size - s);
            set_ref_count(3);
            spawn(splitter1);
            spawn_and_wait_for_all(splitter2);
            tbb::parallel_for(tbb::blocked_range<int>(1, (size + 1) / 2),
                SimpleComparator(mas, size));
        }
        return NULL;
    }
};

void LSDParallelSortDouble(double* inp, int size, int nThreads) {
    double* out = new double[size];
    int portion = size / nThreads;
    if (size % nThreads != 0)
        portion++;
    LSDParallelSorter& sorter = *new (tbb::task::allocate_root())
        LSDParallelSorter(inp, out, size, portion);
    tbb::task::spawn_root_and_wait(sorter);
    delete[] out;
}
