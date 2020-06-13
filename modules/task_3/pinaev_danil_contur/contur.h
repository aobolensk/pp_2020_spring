// Copyright 2020 Pinaev Danil

#ifndef MODULES_TASK_3_PINAEV_DANIL_CONTUR_CONTUR_H_
#define MODULES_TASK_3_PINAEV_DANIL_CONTUR_CONTUR_H_

#include <tbb/tbb.h>

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

class ParallelProcessing {
 private:
    const Image &img;
    Image *res;

 public:
    void operator()(const tbb::blocked_range<int> &r) const;

    ParallelProcessing(const Image &img, Image *res) :
        img(img),
        res(res) {}
};

Image pattalelContur(const Image &in);

#endif  // MODULES_TASK_3_PINAEV_DANIL_CONTUR_CONTUR_H_
