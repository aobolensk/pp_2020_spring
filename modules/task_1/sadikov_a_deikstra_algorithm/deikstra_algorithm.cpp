// Copyright 2020 Sadikov Artem
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>
#include "../../../modules/task_1/sadikov_a_deikstra_algorithm/deikstra_algorithm.h"

std::vector<int> getMinRange(const std::vector<int>& graph, int start, int end) {
    if (start == end)
        return std::vector<int>(1, 0);

    if (start > end) {
        std::swap(start, end);
    }

    int points_count = sqrt(graph.size());
    int max_weight = std::numeric_limits<int>::max();
    int min, min_point, temp;
    std::vector<int> points_len(points_count);
    std::vector<int> way;
    std::vector<bool> visisted(points_count, false);

    --start;
    --end;

    for (int i = 0; i < points_count; i++) {
        points_len[i] = max_weight;
    }

    points_len[start] = 0;

    do {
        min_point = max_weight;
        min = max_weight;

        for (int i = 0; i < points_count; i++) {
            if (!visisted[i] && points_len[i] < min) {
                min_point = i;
                min = points_len[i];
            }
        }

        if (min_point != max_weight) {
            for (int i = 0; i < points_count; i++) {
                if (graph[min_point * points_count + i] > 0) {
                    temp = min + graph[min_point * points_count + i];
                    if (points_len[i] > temp) {
                        points_len[i] = temp;
                    }
                }
            }
            visisted[min_point] = true;
        }
    } while (min_point < max_weight);


    way.push_back(end + 1);
    int weight = points_len[end];

    while (end != start) {
        for (int i = 0; i < points_count; i++) {
            if (graph[end * points_count + i] > 0) {
                temp = weight - graph[end * points_count + i];
                if (points_len[i] == temp) {
                    weight = temp;
                    end = i;
                    way.push_back(i + 1);
                }
            }
        }
    }

    return way;
}
