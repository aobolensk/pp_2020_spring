// Copyright 2020 Koltyushkina Yanina
#ifndef MODULES_TASK_1_KOLTYUSHKINA_YA_RADIX_SORT_FOR_DOUBLE_RADIX_SORT_H_
#define MODULES_TASK_1_KOLTYUSHKINA_YA_RADIX_SORT_FOR_DOUBLE_RADIX_SORT_H_

double* RandMas(int len, double low = 0 , double high = 100);
void RadixSortPart(double *inmas, double**outmas, int len, int byteN);
void RadixSortAll(double**inmas, int len);

#endif  // MODULES_TASK_1_KOLTYUSHKINA_YA_RADIX_SORT_FOR_DOUBLE_RADIX_SORT_H_
