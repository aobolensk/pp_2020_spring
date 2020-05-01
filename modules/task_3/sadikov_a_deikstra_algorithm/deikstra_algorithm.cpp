// Copyright 2020 Sadikov Artem
#include "../../../modules/task_3/sadikov_a_deikstra_algorithm/deikstra_algorithm.h"
#include <tbb/tbb.h>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>
#include <random>
#include <ctime>
#include <iostream>

#define THREADS 4

std::vector<int> getRandGraph(int size) {
    std::vector<int> graph(size * size, 0);
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            graph[i * size + j] = graph[j * size + i] = gen() % 100;
        }
    }

    return graph;
}

std::vector<int> getMinRange(const std::vector<int>& graph, int start, int end) {
    if (start == end)
        return std::vector<int>(1, 0);

    if (start > end) {
        std::swap(start, end);
    }

    int points_count = static_cast<int>(sqrt(graph.size()));
    int max_weight = INT32_MAX;
    int min, min_point, temp;
    tbb::mutex mutex;
    tbb::task_scheduler_init(THREADS);
    std::vector<int> points_len(points_count, max_weight);
    std::vector<int> way;
    std::vector<bool> visisted(points_count, false);
    std::vector<int> min_vals(2, INT32_MAX);

    --start;
    --end;

    points_len[start] = 0;

    do {
        min_vals = tbb::parallel_reduce(
            tbb::blocked_range<int>(0, points_count),
            std::vector<int>(2) = {INT32_MAX, INT32_MAX},
            [&](const tbb::blocked_range<int>& v, std::vector<int> local_min_vals) {
                for (int i = v.begin(); i < v.end(); i++) {
                    if (!visisted[i] && points_len[i] < local_min_vals[0]) {
                        local_min_vals[0] = points_len[i];
                        local_min_vals[1] = i;
                    }
                }
                return local_min_vals;
            },
            [&](std::vector<int> x, std::vector<int> y) {
                if (x[0] < y[0]) {
                    return x;
                }
                return y;
            });

        min_point = min_vals[1];
        min = min_vals[0];

        if (min_point != max_weight) {
            tbb::parallel_for(
                tbb::blocked_range<int>(0, points_count),
                [&](const tbb::blocked_range<int>& v) {
                    for (int i = v.begin(); i < v.end(); i++) {
                        if (graph[min_point * points_count + i] > 0) {
                            mutex.lock();
                            temp = min + graph[min_point * points_count + i];
                            if (points_len[i] > temp) {
                                points_len[i] = temp;
                            }
                            mutex.unlock();
                        }
                    }
                });
            visisted[min_point] = true;
        }
    } while (min_point < max_weight);

    way.push_back(end + 1);
    int weight = points_len[end];

    while (end != start) {
        tbb::parallel_for(
            tbb::blocked_range<int>(0, points_count),
            [&](const tbb::blocked_range<int>& v) {
                for (int i = v.begin(); i < v.end(); i++) {
                    if (graph[end * points_count + i] > 0) {
                        temp = weight - graph[end * points_count + i];
                        if (points_len[i] == temp) {
                            weight = temp;
                            end = i;
                            mutex.lock();
                            way.push_back(i + 1);
                            mutex.unlock();
                        }
                    }
                }
            });
    }

    return way;
}
