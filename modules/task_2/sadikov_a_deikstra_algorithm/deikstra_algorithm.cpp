// Copyright 2020 Sadikov Artem
#include <omp.h>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>
#include <iostream>
#include "../../../modules/task_2/sadikov_a_deikstra_algorithm/deikstra_algorithm.h"


std::vector<int> getMinRange(const std::vector<int>& graph, int start, int end) {
    if (start == end)
        return std::vector<int>(1, 0);

    if (start > end) {
        std::swap(start, end);
    }

    int points_count = sqrt(graph.size());
    int max_weight = std::numeric_limits<int>::max();
    int min_len, min_point, temp;
    std::vector<int> points_len(points_count, max_weight);
    std::vector<int> way;
    std::vector<bool> visited(points_count, false);

    --start;
    --end;

    points_len[start] = 0;

    do {
        min_point = max_weight;
        min_len = max_weight;


        #pragma omp parallel
        {
            int local_min_point = max_weight;
            int local_min_len = max_weight;

            #pragma omp for
            for (int i = 0; i < points_count; i++) {
                if (!visited[i] && points_len[i] < local_min_len) {
                    local_min_len = points_len[i];
                    local_min_point = i;
                }
            }

            #pragma omp critical
            {
                if (local_min_len < min_len) {
                    min_len = local_min_len;
                    min_point = local_min_point;
                }
            }
        }

        if (min_point != max_weight) {
            #pragma omp parallel for private(temp)
            for (int i = 0; i < points_count; i++) {
                if (graph[min_point * points_count + i] > 0) {
                    temp = min_len + graph[min_point * points_count + i];
                    if (points_len[i] > temp) {
                        points_len[i] = temp;
                    }
                }
            }
            visited[min_point] = true;
        }
    } while (min_point < max_weight);

    way.push_back(end + 1);
    int weight = points_len[end];

    while (end != start) {
        #pragma omp parallel for private(temp)
        for (int i = 0; i < points_count; i++) {
            if (graph[end * points_count + i] > 0) {
                temp = weight - graph[end * points_count + i];
                if (points_len[i] == temp) {
                    #pragma omp critical
                    {
                        weight = temp;
                        end = i;
                        way.push_back(i + 1);
                    }
                }
            }
        }
    }

    return way;
}
