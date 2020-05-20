// Copyright 2020 Denisov Vladislav
#include "../../../modules/task_4/denisov_v_monte_karlo/monte_karlo.h"

#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <random>
#include <iostream>

static const int countThreads = 2;

double getIntegralMonteCarloPar(const std::function<double(const std::vector<double>&)>& func,
    const std::vector<double>& lowLimInt, const std::vector<double>& highLimInt,
    const unsigned int numberPoints, const int seed) {

    // Exceptions
    if (numberPoints == 0)
        throw "The number of points must be greater than zero";
    if (lowLimInt.empty() || highLimInt.empty())
        throw "Integration limits are not set";
    if (lowLimInt.size() != highLimInt.size())
        throw "The dimensions for the integration limits do not match.";

    std::thread* threads = new std::thread[countThreads];
    std::mutex mutex;

    int delta = numberPoints / countThreads;
    int remainder = numberPoints % countThreads;

    // Prepare random-generation
    unsigned int countDims = static_cast<unsigned int>(lowLimInt.size());
    std::vector<std::uniform_real_distribution<double> > randPoints(countDims);
    for (unsigned int i = 0; i < countDims; i++)
        randPoints[i] = std::uniform_real_distribution<double>(lowLimInt[i], highLimInt[i]);

    double result = 0;
    // Monte-Carlo random
    for (int i = 0; i < countThreads; ++i) {
        threads[i] = std::thread([&](int begin, int end, const int idThread) {
            std::vector<double> point(countDims);
            std::mt19937 generator(seed + idThread);
            double partRes = 0;
            if (idThread == countThreads - 1)
                end += remainder;
            for (int i = begin; i < end; ++i) {
                for (int j = 0; j < static_cast<int>(countDims); j++)
                    point[j] = randPoints[j](generator);
                partRes += func(point);
            }
            std::lock_guard<std::mutex> lock(mutex);
            result += partRes;
            }, i * delta, i * delta + delta, i);
    }

    for (int i = 0; i < countThreads; ++i) {
        threads[i].join();
    }

    // Monte-Carlo calc
    for (unsigned int i = 0; i < countDims; i++) {
        result *= (highLimInt[i] - lowLimInt[i]);
    }
    result /= numberPoints;

    delete[] threads;
    return result;
}

double getIntegralMonteCarloSeq(const std::function<double(const std::vector<double>&)>& func,
    const std::vector<double>& lowLimInt, const std::vector<double>& highLimInt,
    const unsigned int numberPoints, const int seed) {

    // Exceptions
    if (numberPoints == 0)
        throw "The number of points must be greater than zero";
    if (lowLimInt.empty() || highLimInt.empty())
        throw "Integration limits are not set";
    if (lowLimInt.size() != highLimInt.size())
        throw "The dimensions for the integration limits do not match.";

    // Init
    double result = 0.0;
    std::mt19937 generator;
    generator = std::mt19937(seed);
    unsigned int countDims = static_cast<unsigned int>(lowLimInt.size());

    // Prepare random-generation
    std::vector<std::uniform_real_distribution<double> > randPoints(countDims);
    for (unsigned int i = 0; i < countDims; i++)
        randPoints[i] = std::uniform_real_distribution<double>(lowLimInt[i], highLimInt[i]);

    // Monte-Carlo random
    std::vector<double> point(countDims);
    for (unsigned int i = 0; i < numberPoints; i++) {
        for (unsigned int j = 0; j < countDims; j++)
            point[j] = randPoints[j](generator);
        result += func(point);
    }

    // Monte-Carlo calc
    for (unsigned int i = 0; i < countDims; i++) {
        result *= (highLimInt[i] - lowLimInt[i]);
    }
    result /= numberPoints;

    return result;
}
