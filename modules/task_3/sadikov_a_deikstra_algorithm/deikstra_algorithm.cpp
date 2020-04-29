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

std::vector<int> getRandGraph(int size) {
    if (size < 1)
        throw "ERR";
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

    int points_count = sqrt(graph.size());
    int max_weight = INT8_MAX;
    int min, min_point, temp;
    tbb::mutex mutex;
    std::vector<int> points_len(points_count, max_weight);
    std::vector<int> way;
    std::vector<bool> visisted(points_count, false);

    --start;
    --end;

    points_len[start] = 0;

    do {
        min_point = max_weight;
        min = max_weight;

        tbb::parallel_for(
            tbb::blocked_range<int>(0, points_count),
            [&](const tbb::blocked_range<int>& v) {
                for (int i = v.begin(); i < v.end(); i++) {
                    if (!visisted[i] && points_len[i] < min) {
                        min_point = i;
                        min = points_len[i];
                    }
                }
            });

        if (min_point != max_weight) {
            tbb::parallel_for(
                tbb::blocked_range<int>(0, points_count),
                [&](const tbb::blocked_range<int>& v) {
                    for (int i = v.begin(); i < v.end(); i++) {
                        if (graph[min_point * points_count + i] > 0) {
                            temp = min + graph[min_point * points_count + i];
                            if (points_len[i] > temp) {
                                points_len[i] = temp;
                            }
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
                        mutex.lock();
                        if (points_len[i] == temp) {
                            weight = temp;
                            end = i;
                            way.push_back(i + 1);
                        }
                        mutex.unlock();
                    }
                }
            });
    }

    return way;
}
