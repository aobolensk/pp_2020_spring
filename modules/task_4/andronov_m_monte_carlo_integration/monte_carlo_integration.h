// Copyright 2020 Andronov Maxim

#ifndef MODULES_TASK_4_ANDRONOV_M_MONTE_CARLO_INTEGRATION_MONTE_CARLO_INTEGRATION_H_
#define MODULES_TASK_4_ANDRONOV_M_MONTE_CARLO_INTEGRATION_MONTE_CARLO_INTEGRATION_H_

#include <vector>
#include <utility>
#include <functional>

double SeqMonteCarloIntegration(const std::function<double(const std::vector
                                    <double>)>& integrand, const std::vector
                        <std::pair<double, double>> intervals, const size_t& N);

double ParallelMonteCarloIntegration(const std::function<double(const std::vector
                                            <double>)>& integrand, const std::vector
                              <std::pair<double, double>> intervals, const int& N);

#endif  // MODULES_TASK_4_ANDRONOV_M_MONTE_CARLO_INTEGRATION_MONTE_CARLO_INTEGRATION_H_

