// Copyright 2020 Vlasov Andrey
#ifndef MODULES_TASK_1_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_
#define MODULES_TASK_1_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_

#include <vector>

double getIntegralSimpsonSequentional(double(*f)(std::vector<double>), const std::vector<double>& a,
  const std::vector<double>& b, int n);

#endif  // MODULES_TASK_1_VLASOV_A_MULTI_INTEGRATION_SIMPSON_MULTI_INTEGRATION_SIMPSON_H_
