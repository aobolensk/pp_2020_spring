// Copyright 2020 Zhivaev Artem

#ifndef MODULES_TASK_1_ZHIVAEV_A_STRASSEN_MULT_STRASSEN_MULT_H_
#define MODULES_TASK_1_ZHIVAEV_A_STRASSEN_MULT_STRASSEN_MULT_H_

void strassenMultSeq(unsigned int side, const double* a, const double* b,
                     double* result);

void multSeq(unsigned int side, const double* a, const double* b,
             double* result);

int powerOf2(unsigned int number);

void splitMatrix(unsigned int side, const double* a, double* a11, double* a12,
                 double* a21, double* a22);
void assembleMatrix(unsigned int side, double* a, const double* a11,
                    const double* a12, const double* a21, const double* a22);

void matrixSum(unsigned int side, const double* a, const double* b, double* c);
void matrixSub(unsigned int side, const double* a, const double* b, double* c);

#endif  // MODULES_TASK_1_ZHIVAEV_A_STRASSEN_MULT_STRASSEN_MULT_H_
