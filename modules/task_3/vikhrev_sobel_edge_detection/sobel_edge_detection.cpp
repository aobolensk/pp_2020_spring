// Copyright 2020 Vikhrev Ivan
#include <tbb/tbb.h>
#include "../../../modules/task_3/vikhrev_sobel_edge_detection/sobel_edge_detection.h"

class tbbsobel {
 private:
     const imageU& img;
     imageU* res;

 public:
     tbbsobel(const imageU& s, imageU* r) : img{s}, res{r} {}
     void operator() (const tbb::blocked_range<int> &range) const {
        imageS kernX(3, 3, { 1, 0, -1, 2, 0, -2, 1, 0, -1 });
        imageS kernY(3, 3, { 1, 2, 1, 0, 0, 0, -1, -2, -1 });
        for (int i = range.begin(); i != range.end(); ++i) {
            for (int j = 0; j < img.cols; ++j) {
                int id = i * img.cols + j;
                int idk = 0;
                int x{ 0 }, y{ 0 };
                for (int n = kernX.rows/(-2); n <= kernX.rows / 2; ++n) {
                    for (int m = kernX.cols/(-2); m <= kernX.cols/2; ++m) {
                        int row = i + n;
                        int col = j + m;
                        if (row >= 0 && col >= 0 && row < img.rows && col < img.cols) {
                            x +=  kernX.data[idk] * img.data[row * img.cols + col];
                            y +=  kernY.data[idk] * img.data[row * img.cols + col];
                        }
                        ++idk;
                    }
                }
                res->data[id] = sqrt(x*x + y * y) > 255 ? 255 : sqrt(x*x + y * y);
                x = 0;
                y = 0;
            }
        }
    }
};

imageU sobel_par(const imageU& img) {
    imageU res{ img.rows, img.cols };
    tbbsobel  body(img, &res);
    tbb::parallel_for(tbb::blocked_range<int>(0, img.rows), body);
    return res;
}

imageU sobel_seq(const imageU& img) {
    imageS kernX(3, 3, { 1, 0, -1, 2, 0, -2, 1, 0, -1 });
    imageS kernY(3, 3, { 1, 2, 1, 0, 0, 0, -1, -2, -1 });
    int x{ 0 }, y{ 0 };
    imageU res{ img.rows, img.cols };
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            int id = i * img.cols + j;
            int idk = 0;
            for (int n = kernX.rows / (-2); n <= kernX.rows / 2; ++n) {
                for (int m = kernX.cols / (-2); m <= kernX.cols / 2; ++m) {
                    int row = i + n;
                    int col = j + m;
                    if (row >= 0 && col >= 0 && row < img.rows && col < img.cols) {
                        x += kernX.data[idk] * img.data[row * img.cols + col];
                        y += kernY.data[idk] * img.data[row * img.cols + col];
                    }
                    ++idk;
                }
            }
            res.data[id] = sqrt(x*x + y * y) > 255 ? 255 : sqrt(x*x + y * y);
            x = 0;
            y = 0;
        }
    }
    return res;
}
