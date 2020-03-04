// Copyright 2020 Zhivaev Artem

#ifndef MODULES_TASK_1_ZHIVAEV_A_STRASSEN_MULT_STRASSEN_MULT_H_
#define MODULES_TASK_1_ZHIVAEV_A_STRASSEN_MULT_STRASSEN_MULT_H_

void strassenMultSeq(size_t side, const double* a, const double* b, double* result);

void multSeq(size_t side, const double* a, const double* b, double* result);

int powerOf2(size_t number);

void splitMatrix(size_t side, const double* a, double* a11, double* a12,
                 double* a21, double* a22);

void assembleMatrix(size_t side, double* a, const double* a11,
                    const double* a12, const double* a21, const double* a22);

#endif  // MODULES_TASK_1_ZHIVAEV_A_STRASSEN_MULT_STRASSEN_MULT_H_
