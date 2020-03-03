// Copyright 2020 Savkin Yuriy
#include <omp.h>
#include <cstring>
#include <cstddef>
#include <vector>
#include <array>
#include <limits>
#include <utility>
#include <stack>
#include "../../../modules/task_2/savkin_y_radix_sort_simple_merge_double/radix_sort_simple_merge_double.h"

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

    class RadixTask {
     public:
        virtual ~RadixTask() {
        }

        virtual void execute() = 0;
    };

    struct RadixTaskInfo {
        RadixTask* rt;
        std::vector<size_t> childs;
        size_t ref_count;
    };

    class SortFunctor: public RadixTask {
     private:
        radixDouble* arr;
        size_t size;
        radixDouble* buf;

     public:
        SortFunctor(radixDouble* arr_, size_t size_, radixDouble* buf_):
            RadixTask(), arr(arr_), size(size_), buf(buf_) {
        }

        void execute() {
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
        }
    };

    class RewriteFunctor: public RadixTask {
     private:
        double* arr;
        double* out;
        size_t size;

     public:
        RewriteFunctor(double* arr_, double* out_, size_t size_) :
            RadixTask(), arr(arr_), out(out_), size(size_) {
        }

        void execute() {
            for (size_t i = 0; i < size; ++i)
                out[i] = arr[i];
        }
    };

    class MergeFunctor: public RadixTask {
     private:
        double* arr1;
        double* arr2;
        size_t size1;
        size_t size2;
        double* out;

     public:
        MergeFunctor(double* arr1_, double* arr2_, size_t size1_, size_t size2_, double* out_) :
            RadixTask(), arr1(arr1_), arr2(arr2_), size1(size1_), size2(size2_), out(out_) {
        }

        void execute() {
            size_t x = 0, y = 0;
            for (size_t i = 0; i < size1 + size2; ++i) {
                if (x >= size1) {
                    out[i] = arr2[y++];
                } else if (y >= size2) {
                    out[i] = arr1[x++];
                } else if (arr1[x] < arr2[y]) {
                    out[i] = arr1[x++];
                } else {
                    out[i] = arr2[y++];
                }
            }
        }
    };

    class ScheduleInit {
     private:
        double** arr;
        double** out;
        size_t* parts_sizes;
        size_t parts_count;
        std::vector<RadixTaskInfo>* vec;

     public:
        ScheduleInit(double** arr_, double** out_, size_t* parts_sizes_, size_t parts_count_,
            std::vector<RadixTaskInfo>* vec_) : arr(arr_), out(out_), parts_sizes(parts_sizes_),
                parts_count(parts_count_), vec(vec_) {
        }

        size_t execute() {
            if (parts_count < 2) {
                std::vector<size_t> v;
                RadixTaskInfo rti {new RewriteFunctor(arr[0], out[0], parts_sizes[0]), v, 0};
                vec->push_back(rti);
                std::swap(arr[0], out[0]);
                return vec->size() - 1;
            }

            size_t parts_half = parts_count / 2;
            size_t ref_count = 0;
            if (parts_count > 2) {
                ScheduleInit si1(arr, out, parts_sizes, parts_half, vec);
                ScheduleInit si2(arr + parts_half, out + parts_half, parts_sizes + parts_half,
                    parts_count - parts_half, vec);
                size_t index1 = si1.execute();
                size_t index2 = si2.execute();
                vec->at(index1).childs.push_back(vec->size());
                vec->at(index2).childs.push_back(vec->size());
                ref_count += 2;
            }

            double* arr1 = arr[0];
            double* arr2 = arr[parts_half];
            size_t size1 = parts_sizes[0];
            size_t size2 = parts_sizes[parts_half];
            double* output = out[0];

            std::vector<size_t> v;
            RadixTaskInfo rti {new MergeFunctor(arr1, arr2, size1, size2, output), v, ref_count};
            vec->push_back(rti);

            std::swap(arr[0], out[0]);
            parts_sizes[0] += parts_sizes[parts_half];
            return vec->size() - 1;
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

    #pragma omp parallel for
    for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(num_threads); ++i) {
        SortFunctor sf(reinterpret_cast<radixDouble*>(arr_ptr[i]), size_ptr[i],
            reinterpret_cast<radixDouble*>(out_ptr[i]));
        sf.execute();
    }

    std::stack<std::pair<ptrdiff_t, RadixTask*>> ready_tasks;
    std::vector<RadixTaskInfo> info_vec;
    size_t solved_tasks = 0;
    ScheduleInit si(arr_ptr, out_ptr, size_ptr, num_threads, &info_vec);

    if (num_threads > 1)
        si.execute();

    for (size_t i = 0; i < info_vec.size(); ++i) {
        if (info_vec[i].ref_count == 0)
            ready_tasks.push({i, info_vec[i].rt});
    }

    omp_lock_t lock;
    omp_init_lock(&lock);

    #pragma omp parallel
    if (num_threads > 1) {
        std::pair<ptrdiff_t, RadixTask*> my_task = { -1, nullptr };
        while (1) {
            bool end = false;
            if (my_task.second != nullptr)
                my_task.second->execute();
            omp_set_lock(&lock);
            if (my_task.second != nullptr) {
                ++solved_tasks;
                for (size_t i : info_vec[my_task.first].childs) {
                    --info_vec[i].ref_count;
                    if (info_vec[i].ref_count == 0) {
                        ready_tasks.push({ i, info_vec[i].rt });
                    }
                }
                my_task = { -1, nullptr };
            }
            if (!ready_tasks.empty()) {
                my_task = ready_tasks.top();
                ready_tasks.pop();
            }
            if (solved_tasks >= info_vec.size())
                end = true;
            omp_unset_lock(&lock);
            if (end)
                break;
        }
    }

    omp_destroy_lock(&lock);

    if (arr != arr_ptr[0]) {
        #pragma omp parallel for
        for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(count); ++i)
            arr[i] = arr_ptr[0][i];
    }

    for (size_t i = 0; i < info_vec.size(); ++i) {
        delete info_vec[i].rt;
    }
    delete[] buf;
    delete[] arr_ptr;
    delete[] out_ptr;
    delete[] size_ptr;
}
