// Copyright 2020 Pinaev Danil

#ifndef MODULES_TASK_1_PINAEV_DANIL_CONTUR_CONTUR_H_
#define MODULES_TASK_1_PINAEV_DANIL_CONTUR_CONTUR_H_

#include <vector>
#include <string>

struct Image {
    std::vector<int> data;
    int cols, rows;

    Image(int cols, int rows) : cols(cols),
                                rows(rows) {
        data = std::vector<int>(cols * rows, 255);
    }
};

Image generateRandomImage(int rows, int cols);
Image getContur(const Image &a);

#endif  // MODULES_TASK_1_PINAEV_DANIL_CONTUR_CONTUR_H_
