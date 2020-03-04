// Copyright 2020 Savkin Yuriy
#include <cstring>
#include <cstddef>
#include <vector>
#include <array>
#include <limits>
#include <utility>
#include <stack>
#include <algorithm>
#define NOMINMAX
#include "tbb/tbb.h"
#include "../../../modules/task_3/savkin_y_radix_sort_simple_merge_double/radix_sort_simple_merge_double.h"

std::vector<double> getRandomVector(size_t size) {
    std::mt19937_64 mt(time(0));
    std::uniform_real_distribution<double> urd(-500.0, 500.0);
    std::vector<double> v(size);
    for (double& i : v)
        i = exp(urd(mt));
    return v;
}

std::vector<double> getRandomVector2(size_t size) {
    std::mt19937_64 mt(time(0));
    std::uniform_real_distribution<double> urd(-100000.0, 100000.0);
    std::vector<double> v(size);
    for (double& i : v)
        i = urd(mt);
    return v;
}

void radixSortForDouble(double* arr, size_t count, size_t num_threads) {
    static const size_t slice_num = sizeof(double) / sizeof(unsigned char);

    union radixDouble {
        double d;
        unsigned char c[slice_num];
    };

    class SortFunctor : public tbb::task {
     private:
        radixDouble* arr;
        size_t size;
        radixDouble* buf;

     public:
        SortFunctor(radixDouble* arr_, size_t size_, radixDouble* buf_):
            tbb::task(), arr(arr_), size(size_), buf(buf_) {
        }

        tbb::task* execute() {
            constexpr size_t counts_reserve = static_cast<size_t>(std::numeric_limits<unsigned char>::max()) + 2;
            constexpr size_t counts_size = static_cast<size_t>(std::numeric_limits<unsigned char>::max()) + 1;
            std::array<size_t, counts_reserve> counts;

            for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(slice_num - 1); ++i) {
                memset(counts.data(), 0, sizeof(size_t) * counts_size);

                for (size_t j = 0; j < size; ++j)
                    ++counts[static_cast<size_t>(arr[j].c[i]) + 1];
                for (size_t j = 2; j < counts_size; ++j)
                    counts[j] += counts[j - 1];
                for (size_t j = 0; j < size; ++j)
                    buf[counts[arr[j].c[i]]++].d = arr[j].d;
                std::swap(arr, buf);
            }

            memset(counts.data(), 0, sizeof(size_t) * counts_size);

            for (size_t j = 0; j < size; ++j) {
                size_t sc = static_cast<size_t>(arr[j].c[slice_num - 1]);
                if (sc == 127) {
                    ++counts[256];
                } else if (sc > 128) {
                    ++counts[sc];
                } else {
                    ++counts[sc + 1];
                }
            }

            for (size_t j = 254; j > 127; --j)
                counts[j] += counts[j + 1];
            counts[0] = counts[128];
            for (size_t j = 1; j < 128; ++j)
                counts[j] += counts[j - 1];

            for (size_t j = 0; j < size; ++j) {
                size_t sc = static_cast<size_t>(arr[j].c[slice_num - 1]);
                if (sc > 127)
                    buf[--counts[sc]].d = arr[j].d;
                else
                    buf[counts[sc]++].d = arr[j].d;
            }
            std::swap(arr, buf);
            return nullptr;
        }
    };

    class MergeFunctor: public tbb::task {
    private:
        double** arr;
        double** out;
        size_t* parts_sizes;
        size_t parts_count;

    public:
        MergeFunctor(double** arr_, double** out_, size_t* parts_sizes_, size_t parts_count_) :
            tbb::task(), arr(arr_), out(out_), parts_sizes(parts_sizes_), parts_count(parts_count_) {
        }

        tbb::task* execute() {
            if (parts_count < 2) {
                SortFunctor* sf = new(allocate_child()) SortFunctor(reinterpret_cast<radixDouble*>(arr[0]),
                    parts_sizes[0], reinterpret_cast<radixDouble*>(out[0]));
                set_ref_count(2);
                spawn_and_wait_for_all(*sf);
                for (size_t i = 0; i < parts_sizes[0]; ++i)
                    out[0][i] = arr[0][i];
                std::swap(arr[0], out[0]);
                return nullptr;
            }

            size_t parts_half = parts_count / 2;
            tbb::task_list tl;
            if (parts_count > 2) {
                MergeFunctor* mf1 = new(allocate_child()) MergeFunctor(arr, out, parts_sizes, parts_half);
                MergeFunctor* mf2 = new(allocate_child()) MergeFunctor(arr + parts_half, out + parts_half,
                    parts_sizes + parts_half, parts_count - parts_half);
                tl.push_back(*mf1);
                tl.push_back(*mf2);
            } else {
                SortFunctor* sf1 = new(allocate_child()) SortFunctor(reinterpret_cast<radixDouble*>(arr[0]),
                    parts_sizes[0], reinterpret_cast<radixDouble*>(out[0]));
                SortFunctor* sf2 = new(allocate_child()) SortFunctor(reinterpret_cast<radixDouble*>(arr[parts_half]),
                    parts_sizes[parts_half], reinterpret_cast<radixDouble*>(out[parts_half]));
                tl.push_back(*sf1);
                tl.push_back(*sf2);
            }
            set_ref_count(3);
            spawn_and_wait_for_all(tl);

            double* arr1 = arr[0];
            double* arr2 = arr[parts_half];
            size_t size1 = parts_sizes[0];
            size_t size2 = parts_sizes[parts_half];
            double* output = out[0];

            size_t x = 0, y = 0;
            for (size_t i = 0; i < size1 + size2; ++i) {
                if (x >= size1) {
                    output[i] = arr2[y++];
                } else if (y >= size2) {
                    output[i] = arr1[x++];
                } else if (arr1[x] < arr2[y]) {
                    output[i] = arr1[x++];
                } else {
                    output[i] = arr2[y++];
                }
            }

            std::swap(arr[0], out[0]);
            parts_sizes[0] += parts_sizes[parts_half];
            return nullptr;
        }
    };

    double* buf = new double[count];
    double** arr_ptr = new double*[num_threads];
    double** out_ptr = new double*[num_threads];
    size_t* size_ptr = new size_t[num_threads];

    arr_ptr[0] = arr;
    out_ptr[0] = buf;
    for (size_t i = 0; i < num_threads; ++i) {
        size_ptr[i] = count / num_threads + ((count % num_threads > i)? 1 : 0);
    }

    for (size_t i = 1; i < num_threads; ++i) {
        arr_ptr[i] = arr_ptr[i - 1] + size_ptr[i - 1];
        out_ptr[i] = out_ptr[i - 1] + size_ptr[i - 1];
    }

    if (num_threads > 1) {
        MergeFunctor* mf = new(tbb::task::allocate_root()) MergeFunctor(arr_ptr, out_ptr, size_ptr, num_threads);
        tbb::task::spawn_root_and_wait(*mf);
        if (arr != arr_ptr[0]) {
            for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(count); ++i)
                arr[i] = arr_ptr[0][i];
        }
    } else {
        SortFunctor* sf = new(tbb::task::allocate_root()) SortFunctor(reinterpret_cast<radixDouble*>(arr), count,
            reinterpret_cast<radixDouble*>(buf));
        tbb::task::spawn_root_and_wait(*sf);
    }

    delete[] buf;
    delete[] arr_ptr;
    delete[] out_ptr;
    delete[] size_ptr;
}
