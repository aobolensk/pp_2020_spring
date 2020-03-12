// Copyright 2020 Pinaev Danil
#ifndef MODULES_TASK_1_PINAEV_D_CONTUR_H_
#define MODULES_TASK_1_PINAEV_D_CONTUR_H_
// #include <cstdint>
#include <vector>

Class Image {
    public:

    std::vector<int> data;
    int cols, rows;

    Image(int cols, int rows) : cols(cols),
                                rows(rows)
    {
        data = std::vector(cols * rows) = {0};
    }
};

Image generateRandomImage(int rows, int cols);
Image gaussianFilter(const Image &a, int rows, int cols);

#endif  // MODULES_TASK_1_PINAEV_D_CONTUR_H_
