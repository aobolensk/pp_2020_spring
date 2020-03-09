// Copyright 2020 Vlasov Andrey
#ifndef MODULES_TASK_2_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_
#define MODULES_TASK_2_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_

#include <omp.h>
#include <vector>
#include <functional>

double getIntegralSimpsonOpenMP(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n);

double getSum(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n);

double getSum_odd(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n);

#endif  // MODULES_TASK_2_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_
