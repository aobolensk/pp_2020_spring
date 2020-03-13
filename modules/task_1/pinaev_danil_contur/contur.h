// Copyright 2020 Pinaev Danil

#ifndef MODULES_TASK_1_PINAEV_D_CONTUR_H_
#define MODULES_TASK_1_PINAEV_D_CONTUR_H_

#include <vector>

class Image {
    public:

    std::vector<int> data;
    int cols, rows;

    Image(int cols, int rows) : cols(cols),
                                rows(rows)
    {
        data = std::vector<int>(cols * rows) = {0};
    }
};

Image generateRandomImage(int rows, int cols);
Image getContur(const Image &a);

#endif  // MODULES_TASK_1_PINAEV_D_CONTUR_H_
