// Copyright 2020 Vlasov Andrey
#ifndef MODULES_TASK_4_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_
#define MODULES_TASK_4_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_

#include <vector>
#include <functional>

double getIntegralSimpsonThread(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n, int num_threads = 2);

double getSum(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n);

double getSum_odd(const std::function<double(const std::vector<double>&)>& f,
  const std::vector<double>& a, const std::vector<double>& b, int n);

#endif  // MODULES_TASK_4_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_
