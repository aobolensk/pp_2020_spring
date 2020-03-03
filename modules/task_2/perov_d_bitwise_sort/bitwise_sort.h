// Copyright diper1998
#ifndef MODULES_TASK_2_PEROV_D_BITWISE_SORT_BITWISE_SORT_H_
#define MODULES_TASK_2_PEROV_D_BITWISE_SORT_BITWISE_SORT_H_

#include <omp.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

std::vector<double> GetRandomVector(int size);
void BitwiseSort(std::vector<double>::iterator first,
                 std::vector<double>::iterator last);
void BitSort(std::vector<double>* my_vector, int power);
int GetMaxPower(std::vector<double>::iterator first,
                std::vector<double>::iterator last);
int GetOnPower(double value, int power);
int GetOnPowerMantis(double value, int power, int max_power);
int GetMaxMantis(std::vector<double> my_vector, int start, int end);
void DoppelgangerSort(std::vector<double>* my_vector);
void BitSortMantis(std::vector<double>* my_vector, int start, int end,
                   int power, int max_power);

void MergeSort(std::vector<double>::iterator first,
               std::vector<double>::iterator middle,
               std::vector<double>::iterator end);

void MPSort(std::vector<double>::iterator first,
            std::vector<double>::iterator end, int num_th);

void OMPSort(std::vector<double>::iterator first,
             std::vector<double>::iterator end, int num_th);

bool IsSorted(std::vector<double>* old_vector, std::vector<double>* new_vector);

#endif  // MODULES_TASK_2_PEROV_D_BITWISE_SORT_BITWISE_SORT_H_
