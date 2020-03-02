// Copyright diper1998
#ifndef MODULES_TASK_1_PEROV_D_BITWISE_SORT_BITWISE_SORT_H_
#define MODULES_TASK_1_PEROV_D_BITWISE_SORT_BITWISE_SORT_H_

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

std::vector<double> GetRandomVector(int size);
void BitwiseSort(std::vector<double>::iterator first,
                                std::vector<double>::iterator last);
void BitSort(std::vector<double>* my_vector, int power);
int GetMaxPower(std::vector<double> my_vector);
int GetOnPower(double value, int power);
int GetOnPowerMantis(double value, int power, int max_power);
int GetMaxMantis(std::vector<double> my_vector, int start, int end);
void DoppelgangerSort(std::vector<double>* my_vector);
void BitSortMantis(std::vector<double>* my_vector, int start, int end,
                   int power, int max_power);
bool IsSorted(std::vector<double>* old_vector, std::vector<double>* new_vector);

#endif  // MODULES_TASK_1_PEROV_D_BITWISE_SORT_BITWISE_SORT_H_
