// Copyright 2020 diper1998
// #include "bitwise_sort.h"
#include "../../../modules/task_1/perov_d_bitwise_sort/bitwise_sort.h"
#include <algorithm>
#include <ctime>
#include <random>
#include <vector>

std::vector<double> GetRandomVector(int size) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<double> my_vector(size);
  for (int i = 0; i < size; ++i) {
    my_vector[i] = (gen() % 1000) / (i + 1.0);
    if (i % 2 == 0) my_vector[i] *= -1;
  }
  return my_vector;
}

int GetMaxMantis(std::vector<double> my_vector, int start, int end) {
  int max_power = 0;
  int power = 0;
  for (int i = start; i <= end; ++i) {
    power = 0;
    double mantis =
        std::abs(my_vector[i]) - static_cast<int>(std::abs(my_vector[i]));
    double dif = mantis;
    while (dif != 0 && power != 8) {
      power++;
      mantis *= 10;
      dif = mantis - static_cast<int>(mantis);
    }

    if (power > max_power) {
      max_power = power;
    }
  }
  // + size
  return max_power;
}

int GetMaxPower(std::vector<double>::iterator first,
                std::vector<double>::iterator last) {
  int max_power = 0;
  int power = 0;
  for (auto i = first; i != last; ++i) {
    power = 0;
    int tmp = static_cast<int>(*i);
    while (tmp != 0) {
      power++;
      tmp = tmp / 10;
    }
    if (power > max_power) {
      max_power = power;
    }
  }
  return max_power;
}

int GetOnPower(double value, int power) {
  return std::abs(static_cast<int>(static_cast<int>(value) %
                                   (static_cast<int>(pow(10, power))) /
                                   (pow(10, power - 1))));
}

int GetOnPowerMantis(double value, int power, int max_power) {
  double mantis = (value - static_cast<int>(value)) * pow(10, max_power);

  return GetOnPower(mantis, power);
}

void BitSortMantis(std::vector<double>* my_vector, int start, int end,
                   int power, int max_power) {
  std::vector<double> tmp_vector;

  for (int i = start; i <= end; ++i) {
    tmp_vector.push_back(my_vector->at(i));
  }

  std::vector<double> res_vector(tmp_vector);

  std::vector<int> counter(10, 0);
  int on_power = 0;

  for (unsigned int i = 0; i < tmp_vector.size(); ++i) {
    on_power = GetOnPowerMantis(tmp_vector[i], power, max_power);
    counter[on_power]++;
  }

  std::vector<int> counter_tmp(10, 0);

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < i; ++j) {
      counter_tmp[i] += counter[j];
    }
  }

  for (unsigned int i = 0; i < tmp_vector.size(); ++i) {
    res_vector[counter_tmp[GetOnPowerMantis(tmp_vector[i], power,
                                            max_power)]++] = tmp_vector[i];
  }

  int id = 0;

  for (int i = start; i <= end; ++i) {
    my_vector->at(i) = res_vector[id++];
  }
}

void BitSort(std::vector<double>* my_vector, int power) {
  std::vector<double> res_vector(*my_vector);

  std::vector<int> counter(10, 0);
  int on_power = 0;

  for (unsigned int i = 0; i < my_vector->size(); ++i) {
    on_power = GetOnPower(my_vector->at(i), power);
    counter[on_power]++;
  }

  std::vector<int> counter_tmp(10, 0);

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < i; ++j) {
      counter_tmp[i] += counter[j];
    }
  }

  for (unsigned int i = 0; i < my_vector->size(); i++) {
    res_vector[counter_tmp[GetOnPower(my_vector->at(i), power)]++] =
        my_vector->at(i);
  }

  for (unsigned int i = 0; i < my_vector->size(); i++) {
    my_vector->at(i) = res_vector[i];
  }
}

void DoppelgangerSort(std::vector<double>* my_vector) {
  for (unsigned int i = 0; i < my_vector->size() - 1; i++) {
    int doppelganger = 0;
    int start;
    int end;

    if (static_cast<int>(my_vector->at(i)) ==
        static_cast<int>(my_vector->at(i + 1))) {
      start = i;
      i++;
      doppelganger++;

      while (i < my_vector->size() - 1 &&
             (static_cast<int>(my_vector->at(i)) ==
              static_cast<int>(my_vector->at(i + 1)))) {
        i++;
        doppelganger++;
      }
      end = start + doppelganger;

      int power_mantis = GetMaxMantis(*my_vector, start, end);

      for (int j = 1; j <= power_mantis; j++) {
        BitSortMantis(my_vector, start, end, j, power_mantis);
      }
    }
  }
}

void BitwiseSort(std::vector<double>::iterator first,
                 std::vector<double>::iterator last) {
  std::vector<double> positiv_vector;
  std::vector<double> negativ_vector;

  int power = GetMaxPower(first, last);

  for (auto i = first; i != last; ++i) {
    if (*i >= 0)
      positiv_vector.push_back(*i);
    else
      negativ_vector.push_back(*i);
  }

  if (negativ_vector.size() != 0) {
    for (int i = 1; i <= power; ++i) {
      BitSort(&negativ_vector, i);
    }
    DoppelgangerSort(&negativ_vector);
  }

  if (positiv_vector.size() != 0) {
    for (int i = 1; i <= power; ++i) {
      BitSort(&positiv_vector, i);
    }
    DoppelgangerSort(&positiv_vector);
  }

  auto id = first;

  for (int i = negativ_vector.size() - 1; i >= 0; --i) {
    *id = negativ_vector[i];
    id++;
  }

  for (unsigned int i = 0; i < positiv_vector.size(); i++) {
    *id = positiv_vector[i];
    id++;
  }
}

bool IsSorted(std::vector<double>* old_vector,
              std::vector<double>* new_vector) {
  std::sort(old_vector->begin(), old_vector->end());

  bool flag = true;
  for (unsigned int i = 0; i < old_vector->size(); i++) {
    if (old_vector->at(i) != new_vector->at(i)) {
      if (std::abs(old_vector->at(i) - new_vector->at(i)) >= 0.0000001) {
        flag = false;
        break;
      }
    }
  }

  return flag;
}
