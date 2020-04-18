// Copyright 2020 Gaydaychuk Yury
#include <omp.h>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include <algorithm>
#include <utility>
#include "../../../modules/task_2/gaydaychuk_bitwise_oddeven_sort/bitwise_oddeven_sort.h"

#define MINIMAL_SINGLE_ARRAY_LENGTH 2

void NetworkBuilder::setNetworkSize(int size) {
        this->size = size;
        twoDegree = 1;
        while (twoDegree < size) {
            twoDegree *= 2;
        }
        indexArray.clear();
        for (int i = 0; i < twoDegree; i++) {
            indexArray.push_back(i);
        }
        auxiliaryNodeSetArray.clear();
        parallelBlockArray.clear();
    }
void NetworkBuilder::computeNetwork() {
    pseudoSort_2(0, static_cast<int>(indexArray.size()));
}

void NetworkBuilder::pseudoSort_2(int lo, int n) {
    if (n > 1) {
        int m = n / 2;
        pseudoSort_2(lo, m);
        pseudoSort_2(lo + m, m);
        bMerge_2(lo, n, 1);
    }
}

void NetworkBuilder::bMerge_2(int lo, int n, int r) {
    // lo is the starting position and
    // n is the length of the piece to be merged,
    // r is the distance of the elements to be compared
    int m = r * 2;
    if (m < n) {
        bMerge_2(lo, n, m);      // even subsequence
        bMerge_2(lo + r, n, m);    // odd subsequence
        for (int i = lo + r; i + r < lo + n; i += m) {
            comparatorArray.push_back(std::pair<int, int>(
                indexArray[i], indexArray[i + r]));
            addComparatorAnother(indexArray[i], indexArray[i + r]);
            // addComparator(indexArray[i], indexArray[i + r]);
        }
    } else {
        addComparatorAnother(indexArray[lo], indexArray[lo + r]);
        // addComparator(indexArray[lo], indexArray[lo + r]);
        comparatorArray.push_back(std::pair<int, int>(
            indexArray[lo], indexArray[lo + r]));
    }
}

void NetworkBuilder::addComparator(int i, int j) {
    if (auxiliaryNodeSetArray.empty()) {
        std::vector<int> newBlockNodeSet;

        newBlockNodeSet.push_back(i);
        newBlockNodeSet.push_back(j);
        auxiliaryNodeSetArray.push_back(newBlockNodeSet);

        std::vector<std::pair <int, int> > newBlock;
        newBlock.push_back(std::pair<int, int>(i, j));
        parallelBlockArray.push_back(newBlock);
    } else {
        bool pairAndSetIntersectionFound = false;
        std::list<std::vector<std::pair <int, int> > >::iterator
        parallelBlocksIterator = parallelBlockArray.begin();
        for (
            std::list<std::vector<int > >::iterator
            itBlocks = auxiliaryNodeSetArray.begin();
            itBlocks != auxiliaryNodeSetArray.end();
            ++itBlocks) {
            pairAndSetIntersectionFound = false;
            auto currBlock = *itBlocks;
            for (
                std::vector<int> ::iterator itInBlock = currBlock.begin();
                itInBlock != currBlock.end(); ++itInBlock) {
                if (i == *itInBlock || j == *itInBlock) {
                    pairAndSetIntersectionFound = true;
                    break;
                }
            }
            if (pairAndSetIntersectionFound == true) {
                  if (
                      (itBlocks != auxiliaryNodeSetArray.end())
                      && (next(itBlocks) == auxiliaryNodeSetArray.end())) {
                    auxiliaryNodeSetArray.push_back({i, j});
                    parallelBlockArray.push_back(
                        std::vector<std::pair <int, int> >(
                        {std::pair <int, int>(i, j)}));
                    break;
                } else {
                    continue;
                }
            } else {
                parallelBlocksIterator->push_back(std::pair<int, int>(i, j));
                itBlocks->push_back(i);
                itBlocks->push_back(j);
                break;
            }
            ++parallelBlocksIterator;
        }
    }
}

void NetworkBuilder::addComparatorAnother(int i, int j) {
    if (auxiliaryNodeSetArray.empty()) {
        std::vector<int> newBlockNodeSet;

        newBlockNodeSet.push_back(i);
        newBlockNodeSet.push_back(j);
        auxiliaryNodeSetArray.push_back(newBlockNodeSet);

        std::vector<std::pair <int, int> > newBlock;
        newBlock.push_back(std::pair<int, int>(i, j));
        parallelBlockArray.push_back(newBlock);
    } else {
        bool pairAndSetIntersectionFound = false;
        std::list<std::vector<std::pair <int, int> > >::reverse_iterator
        parallelBlocksIterator =
        parallelBlockArray.rbegin();
        for (
            std::list<std::vector<int > >::reverse_iterator  itBlocks =
            auxiliaryNodeSetArray.rbegin();
            itBlocks != auxiliaryNodeSetArray.rend();
            ++itBlocks) {
            pairAndSetIntersectionFound = false;
            auto currBlock = *itBlocks;
            for (std::vector<int> ::iterator itInBlock = currBlock.begin();
            itInBlock != currBlock.end(); ++itInBlock) {
                if (i == *itInBlock || j == *itInBlock) {
                    pairAndSetIntersectionFound = true;
                    break;
                }
            }
            if (pairAndSetIntersectionFound == true) {
                if (itBlocks == auxiliaryNodeSetArray.rbegin()) {
                    auxiliaryNodeSetArray.push_back({i, j});
                    parallelBlockArray.push_back(
                        std::vector<std::pair <int, int> >(
                        {std::pair <int, int>(i, j)}));
                    break;
                } else {
                    --itBlocks;
                    --parallelBlocksIterator;
                    parallelBlocksIterator->push_back(
                        std::pair<int, int>(i, j));
                    itBlocks->push_back(i);
                    itBlocks->push_back(j);
                    break;
                }
            } else {
                if (next(itBlocks) != auxiliaryNodeSetArray.rend()) {
                    ++parallelBlocksIterator;
                    continue;
                } else {
                    parallelBlocksIterator->push_back(
                        std::pair<int, int>(i, j));
                    itBlocks->push_back(i);
                    itBlocks->push_back(j);
                }
            }
            ++parallelBlocksIterator;
        }
    }
}

std::list<std::vector<std::pair <int, int> > >
NetworkBuilder::getParallelBlockArray() {
    computeNetwork();
    // remove unused pairs
    std::list<std::vector<std::pair <int, int> > > shortenedNetwork;
    for (std::list<std::vector<std::pair <int, int> > >::iterator
    itBlocks = parallelBlockArray.begin();
    itBlocks != parallelBlockArray.end();
    ++itBlocks) {
        // auto predicate = [=](const std::pair <int, int> &p)
        // { return p.first >= size || p.second >= size; };
        // auto v = *(itBlocks);
        // v.erase(std::remove_if (v.begin(), v.end(), predicate), v.end());
        std::vector<std::pair <int, int> > currentBlock;
        for (std::vector<std::pair <int, int> >::iterator
        itElements = itBlocks->begin();
        itElements != itBlocks->end();
        ++itElements) {
            if (itElements->first < size && itElements->second < size) {
                currentBlock.push_back(
                    std::pair <int, int>(
                        itElements->first, itElements->second));
            }
        }
        shortenedNetwork.push_back(currentBlock);
    }
    return shortenedNetwork;
}


std::string NetworkBuilder::printComp() {
    std::string result;
    for (std::vector<std::pair<int, int>>::iterator it =
    comparatorArray.begin();
    it != comparatorArray.end(); ++it) {
        if (it->first < 0) {
            result = result + "\t\t";
        }
        if (it->first == 0) {
            result = result + "\t\t\t\t";
        }
        result = result + "Pair: (" + std::to_string(it->first) +
        " ," + std::to_string(it->second) + ")\n";
    }
    result = result + "\nsize = " +
    std::to_string(parallelBlockArray.size()) + "\n";
    return result;
}

std::string NetworkBuilder::getState() { return state; }

std::string NetworkBuilder::printParallelComp() {
    std::string result;
    for (std::list<std::vector<std::pair <int, int> > >::iterator blockIt =
    parallelBlockArray.begin();
    blockIt != parallelBlockArray.end(); ++blockIt) {
        result = result + "\n ------------ \n";
        for (std::vector<std::pair <int, int> >::iterator it = blockIt->begin();
        it != blockIt->end(); ++it) {
            result = result + "Pair: (" + std::to_string(it->first) + " ," +
            std::to_string(it->second) + ")\n";
        }
    }
    return result;
}

std::string NetworkBuilder::printAux() {
    std::string result = "\n ================ \n ==============\n";
    for (std::list<std::vector<int> >::iterator blockIt =
    auxiliaryNodeSetArray.begin();
    blockIt != auxiliaryNodeSetArray.end(); ++blockIt) {
        result = result + "\n ------------ \n";
        for (std::vector<int>::iterator it = blockIt->begin();
        it != blockIt->end(); ++it) {
            result = result + "Aux: " + std::to_string(*it) + "\n";
        }
    }
    return result;
}

void NetworkBuilder::printIndexArray() {
    state = state + "\nIndexArray = ";
    for (std::vector<int>::iterator it = indexArray.begin();
    it != indexArray.end(); ++it) {
        state = state + ", " + std::to_string(*it);
    }
    state = state + "\n";
}

bool checkAscending(std::vector<int> vec) {
    return std::is_sorted(std::begin(vec), std::end(vec));
}

bool checkAscending(int *p, int length) {
    return std::is_sorted(p, p + length);
}

int getMax(std::vector<int> *vec) {
    int n = vec->size();
    int max = vec->at(0);
    for (int i = 1; i < n; i++) {
        if (vec->at(i) > max) {
            max = vec->at(i);
        }
    }
    return max;
}

int getMax(int *p, int length) {
    int max = *p;
    for (int i = 1; i < length; i++) {
        if (*(p + i) > max) {
            max = *(p + i);
        }
    }
    return max;
}

void sortByDigit(std::vector<int> *vec, int digit) {
    int n = vec->size();
    std::vector<int> res(n);
    int i, count[10] = {0};
    for (i = 0; i < n; i++) {
        count[(vec->at(i) / digit) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (i = n - 1; i >= 0; i--) {
        res[count[(vec->at(i) / digit) % 10] - 1] = vec->at(i);
        count[(vec->at(i) / digit) % 10]--;
    }
    for (i = 0; i < n; i++) {
        vec->at(i) = res[i];
    }
}

void sortByDigit(int *p, int length, int digit) {
    std::vector<int> res(length);
    int i, count[10] = {0};
    for (i = 0; i < length; i++) {
        count[((*(p + i)) / digit) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (i = length - 1; i >= 0; i--) {
        res[count[((*(p + i)) / digit) % 10] - 1] = *(p + i);
        count[((*(p + i)) / digit) % 10]--;
    }
    for (i = 0; i < length; i++) {
        *(p + i) = res[i];
    }
}

void bitwiseSort(std::vector<int> *vec) {
    int max = getMax(vec);
    for (int digit = 1; max / digit > 0; digit *= 10) {
        sortByDigit(vec, digit);
    }
}

void bitwiseSortWithTiming(int *p, int length, double *time) {
    double startTime = 0, endTime = 0;
    #pragma omp single
    {
        if (time != nullptr) {
            startTime = omp_get_wtime();
        }
        int max = getMax(p, length);
        for (int digit = 1; max / digit > 0; digit *= 10) {
            sortByDigit(p, length, digit);
        }
        if (time != nullptr) {
            endTime = omp_get_wtime();
            *time = endTime - startTime;
        }
    }
}

void bitwiseSort(int *p, int length) {
    int max = getMax(p, length);
    for (int digit = 1; max / digit > 0; digit *= 10) {
        sortByDigit(p, length, digit);
    }
}

void printThreadNum(int maxThreadNumber) {
    omp_set_num_threads(maxThreadNumber);
    int threadNumber = 0;
    std::string result = "";
#pragma omp parallel private(threadNumber)
    {
        threadNumber = omp_get_thread_num();
#pragma omp critical
        {
        printf("\n ------------- %i", threadNumber);
        }
    }
}

void printThreadArea(int arraySize, int maxThreadCount) {
    int effectiveThreadCount = 0;
    if (arraySize < MINIMAL_SINGLE_ARRAY_LENGTH * maxThreadCount) {
        if (arraySize % MINIMAL_SINGLE_ARRAY_LENGTH == 0) {
            effectiveThreadCount = static_cast<int>(
                arraySize / MINIMAL_SINGLE_ARRAY_LENGTH);
        } else {
            effectiveThreadCount = static_cast<int>((
                arraySize / MINIMAL_SINGLE_ARRAY_LENGTH) + 1);
        }
    } else {
        if (arraySize < (MINIMAL_SINGLE_ARRAY_LENGTH + 1) *
        (maxThreadCount - 1) + 1) {
            effectiveThreadCount = maxThreadCount - 1;
        } else {
            effectiveThreadCount = maxThreadCount;
        }
    }
    omp_set_num_threads(effectiveThreadCount);

    int threadNumber = 0, beginIndex = 0,
    endIndex = 0;  // indexes are supposed to be inclusive
    #pragma omp parallel private(threadNumber, beginIndex, endIndex)
    {
        #pragma omp single
        {
            printf("\n  PRINTING THREAD AREA \n");
        }
        threadNumber = omp_get_thread_num();

        if (threadNumber > effectiveThreadCount) {
            beginIndex = endIndex = -1;  // do nothing
        } else {
            if (arraySize % effectiveThreadCount == 0) {
                int localSize = static_cast<int>(
                    arraySize / effectiveThreadCount);
                beginIndex = threadNumber * localSize;
                endIndex = beginIndex + localSize - 1;
            } else {
                if (effectiveThreadCount == 1) {
                    beginIndex = 0;
                    endIndex = arraySize - 1;
                } else {
                    int localSize = static_cast<int>(
                        (arraySize / effectiveThreadCount) + 1);
                    beginIndex = threadNumber * localSize;
                    if (threadNumber == effectiveThreadCount - 1) {
                        endIndex = arraySize - 1;
                    } else {
                        endIndex = beginIndex + localSize - 1;
                    }
                }
            }
        }
        #pragma omp critical
        {
            printf("\n ------------- \nThreadNumber: %i\t\t"
            "EffectiveThreadCount: %i\t\t"
            "begin: %i\tend: %i\n", threadNumber,
            effectiveThreadCount, beginIndex, endIndex);
        }
    }
}

void mergeAndSplit(int *arr1, int size1, int *arr2, int size2) {
  for (int i = size2 - 1; i >= 0; i--) {
    int j, last = arr1[size1 - 1];
    for (j = size1 - 2; j >= 0 && arr1[j] > arr2[i]; j--)
      arr1[j + 1] = arr1[j];
    if (j != size1 - 2 || last > arr2[i]) {
      arr1[j + 1] = arr2[i];
      arr2[i] = last;
    }
  }
}

bool parallelBitwiseBatcherSort(int *array, int arraySize,
    int maxThreadCount, double *time) {
    double startTime = 0, endTime = 0;
    #pragma omp single
    {
        if (time != nullptr) {
            startTime = omp_get_wtime();
        }
    }
    // definr effective threadCount
    // define areas
    // sort
    // check every one
    std::list<std::vector<std::pair <int, int> > > parallelArray;
    bool allSubarraysSortedCorrectly = true;
    int effectiveThreadCount = 0;
    if (arraySize < MINIMAL_SINGLE_ARRAY_LENGTH * maxThreadCount) {
        if (arraySize % MINIMAL_SINGLE_ARRAY_LENGTH == 0) {
            effectiveThreadCount = static_cast<int>((
                arraySize / MINIMAL_SINGLE_ARRAY_LENGTH));
        } else {
            effectiveThreadCount = static_cast<int>((
                arraySize / MINIMAL_SINGLE_ARRAY_LENGTH) + 1);
        }
    } else {
        if (arraySize < (MINIMAL_SINGLE_ARRAY_LENGTH + 1) *
        (maxThreadCount - 1) + 1) {
            effectiveThreadCount = maxThreadCount - 1;
        } else {
            effectiveThreadCount = maxThreadCount;
        }
    }
    omp_set_num_threads(effectiveThreadCount);

    int threadNumber = 0, beginIndex = 0,
    endIndex = 0;  // indexes are supposed to be inclusive
    #pragma omp parallel private(threadNumber, beginIndex, endIndex)
    {
        #pragma omp single
        {
            if (time == nullptr) {
                printf("\n SORTING OF EACH SUBARRAY \n");
            }
        }
        threadNumber = omp_get_thread_num();

        if (threadNumber > effectiveThreadCount) {
            beginIndex = endIndex = -1;  // do nothing
        } else {
            if (arraySize % effectiveThreadCount == 0) {
                int localSize = static_cast<int>(
                    arraySize / effectiveThreadCount);
                beginIndex = threadNumber * localSize;
                endIndex = beginIndex + localSize - 1;
            } else {
                if (effectiveThreadCount == 1) {
                    beginIndex = 0;
                    endIndex = arraySize - 1;
                } else {
                    int localSize = static_cast<int>(
                        (arraySize / effectiveThreadCount) + 1);
                    beginIndex = threadNumber * localSize;
                    if (threadNumber == effectiveThreadCount - 1) {
                        endIndex = arraySize - 1;
                    } else {
                        endIndex = beginIndex + localSize - 1;
                    }
                }
            }
        }

        bitwiseSort(array + beginIndex, endIndex - beginIndex + 1);
        if (time != nullptr) {
            bool sortedLocally = checkAscending(
                array + beginIndex, endIndex - beginIndex + 1);
            #pragma omp critical
            {
                allSubarraysSortedCorrectly &= sortedLocally;
            }
        }
        #pragma omp barrier
        #pragma omp single
        {
            if (time == nullptr) {
                printf(allSubarraysSortedCorrectly ?
                    "\n ARRAYS SORTED CORRECTLY \n"
                    : "\n ARRAYS SORTED NOT CORRECTLY \n");
            }
            NetworkBuilder nb;
            nb.setNetworkSize(effectiveThreadCount);
            parallelArray =  nb.getParallelBlockArray();
        }
    }
    #pragma omp barrier

    for (auto itBlocks = parallelArray.begin();
    itBlocks != parallelArray.end();
    ++itBlocks) {
        int parallelblockSize = static_cast<int>((itBlocks->size()));
        int sa1 = 0, sa2 = 0;
        int bI1 = 0, eI1 = 0;
        int bI2 = 0, eI2 = 0;
        #pragma omp parallel for private(sa1, sa2, bI1, eI1, bI2, eI2)
        for (int i = 0; i < parallelblockSize; ++i) {
            bI1 = 0, eI1 = 0;
            bI2 = 0, eI2 = 0;
            sa1 = itBlocks->at(i).first;
            sa2 = itBlocks->at(i).second;
            // get areas to merge
            if (arraySize % effectiveThreadCount == 0) {
                int localSize = static_cast<int>((
                    arraySize / effectiveThreadCount));
                bI1 = sa1 * localSize;
                bI2 = sa2 * localSize;

                eI1 = bI1 + localSize - 1;
                eI2 = bI2 + localSize - 1;

            } else {
                if (effectiveThreadCount != 1) {
                    int localSize = static_cast<int>((
                        arraySize / effectiveThreadCount) + 1);
                    bI1 = sa1 * localSize;
                    bI2 = sa2 * localSize;

                    if (sa1 == effectiveThreadCount - 1) {
                        eI1 = arraySize - 1;
                    } else {
                        eI1 = bI1 + localSize - 1;
                    }
                    if (sa2 == effectiveThreadCount - 1) {
                        eI2 = arraySize - 1;
                    } else {
                        eI2 = bI2 + localSize - 1;
                    }
                }
            }
            // merge
            mergeAndSplit(array + bI1, eI1 - bI1 + 1,
            array + bI2, eI2 - bI2 + 1);
        }
        // synchronize the phase
        #pragma omp barrier
        if (time == nullptr) {
            #pragma omp single
            {
                printf("\n PARALLEL MERGING PHASE ENDED \n");
            }
        }
        #pragma omp barrier
    }
    #pragma omp single
    {
        if (time != nullptr) {
            endTime = omp_get_wtime();
            *time = endTime - startTime;
        }
    }
    return checkAscending(array, arraySize);
}

bool parallelBitwiseBatcherSort_for_timing(int *array, int arraySize,
    int maxThreadCount, double *time) {
    double startTime = 0, endTime = 0;
    std::list<std::vector<std::pair <int, int> > > parallelArray;
    bool allSubarraysSortedCorrectly = true;
    int effectiveThreadCount = 0;
    if (arraySize < MINIMAL_SINGLE_ARRAY_LENGTH * maxThreadCount) {
        if (arraySize % MINIMAL_SINGLE_ARRAY_LENGTH == 0) {
            effectiveThreadCount = static_cast<int>((
                arraySize / MINIMAL_SINGLE_ARRAY_LENGTH));
        } else {
            effectiveThreadCount = static_cast<int>((
                arraySize / MINIMAL_SINGLE_ARRAY_LENGTH) + 1);
        }
    } else {
        if (arraySize < (MINIMAL_SINGLE_ARRAY_LENGTH + 1) *
        (maxThreadCount - 1) + 1) {
            effectiveThreadCount = maxThreadCount - 1;
        } else {
            effectiveThreadCount = maxThreadCount;
        }
    }
    omp_set_num_threads(effectiveThreadCount);
    #pragma omp single
    {
        if (time != nullptr) {
            startTime = omp_get_wtime();
        }
    }
    int threadNumber = 0, beginIndex = 0,
    endIndex = 0;  // indexes are supposed to be inclusive
    #pragma omp parallel private(threadNumber, beginIndex, endIndex)
    {
        threadNumber = omp_get_thread_num();

        if (threadNumber > effectiveThreadCount) {
            beginIndex = endIndex = -1;  // do nothing
        } else {
            if (arraySize % effectiveThreadCount == 0) {
                int localSize = static_cast<int>(
                    arraySize / effectiveThreadCount);
                beginIndex = threadNumber * localSize;
                endIndex = beginIndex + localSize - 1;
            } else {
                if (effectiveThreadCount == 1) {
                    beginIndex = 0;
                    endIndex = arraySize - 1;
                } else {
                    int localSize = static_cast<int>(
                        (arraySize / effectiveThreadCount) + 1);
                    beginIndex = threadNumber * localSize;
                    if (threadNumber == effectiveThreadCount - 1) {
                        endIndex = arraySize - 1;
                    } else {
                        endIndex = beginIndex + localSize - 1;
                    }
                }
            }
        }

        bitwiseSort(array + beginIndex, endIndex - beginIndex + 1);
        if (time != nullptr) {
            bool sortedLocally = checkAscending(
                array + beginIndex, endIndex - beginIndex + 1);
            #pragma omp critical
            {
                allSubarraysSortedCorrectly &= sortedLocally;
            }
        }
        #pragma omp barrier
        #pragma omp single
        {
            NetworkBuilder nb;
            nb.setNetworkSize(effectiveThreadCount);
            parallelArray =  nb.getParallelBlockArray();
        }
    }
    #pragma omp barrier
    #pragma omp single
    {
        if (time != nullptr) {
            endTime = omp_get_wtime();
            *time = endTime - startTime;
        }
    }

    for (auto itBlocks = parallelArray.begin();
    itBlocks != parallelArray.end();
    ++itBlocks) {
        int parallelblockSize = static_cast<int>((itBlocks->size()));
        int sa1 = 0, sa2 = 0;
        int bI1 = 0, eI1 = 0;
        int bI2 = 0, eI2 = 0;
        #pragma omp parallel for private(sa1, sa2, bI1, eI1, bI2, eI2)
        for (int i = 0; i < parallelblockSize; ++i) {
            bI1 = 0, eI1 = 0;
            bI2 = 0, eI2 = 0;
            sa1 = itBlocks->at(i).first;
            sa2 = itBlocks->at(i).second;
            // get areas to merge
            if (arraySize % effectiveThreadCount == 0) {
                int localSize = static_cast<int>((
                    arraySize / effectiveThreadCount));
                bI1 = sa1 * localSize;
                bI2 = sa2 * localSize;

                eI1 = bI1 + localSize - 1;
                eI2 = bI2 + localSize - 1;

            } else {
                if (effectiveThreadCount != 1) {
                    int localSize = static_cast<int>((
                        arraySize / effectiveThreadCount) + 1);
                    bI1 = sa1 * localSize;
                    bI2 = sa2 * localSize;

                    if (sa1 == effectiveThreadCount - 1) {
                        eI1 = arraySize - 1;
                    } else {
                        eI1 = bI1 + localSize - 1;
                    }
                    if (sa2 == effectiveThreadCount - 1) {
                        eI2 = arraySize - 1;
                    } else {
                        eI2 = bI2 + localSize - 1;
                    }
                }
            }
            // merge
            mergeAndSplit(array + bI1, eI1 - bI1 + 1,
            array + bI2, eI2 - bI2 + 1);
        }
        // synchronize the phase
        #pragma omp barrier
    }
    return checkAscending(array, arraySize);
}

bool parallelLocalSort(int *array, int arraySize, int maxThreadCount) {
    // define effective threadCount
    // sort everyone at one time
    // check every one
    std::list<std::vector<std::pair <int, int> > > parallelArray;
    bool allSubarraysSortedCorrectly = true;
    int effectiveThreadCount = 0;
    if (arraySize < MINIMAL_SINGLE_ARRAY_LENGTH * maxThreadCount) {
        if (arraySize % MINIMAL_SINGLE_ARRAY_LENGTH == 0) {
            effectiveThreadCount = static_cast<int>((
                arraySize / MINIMAL_SINGLE_ARRAY_LENGTH));
        } else {
            effectiveThreadCount = static_cast<int>((
                arraySize / MINIMAL_SINGLE_ARRAY_LENGTH) + 1);
        }
    } else {
        if (arraySize < (MINIMAL_SINGLE_ARRAY_LENGTH + 1) *
        (maxThreadCount - 1) + 1) {
            effectiveThreadCount = maxThreadCount - 1;
        } else {
            effectiveThreadCount = maxThreadCount;
        }
    }
    omp_set_num_threads(effectiveThreadCount);

    int threadNumber = 0, beginIndex = 0,
    endIndex = 0;  // indexes are supposed to be inclusive
    #pragma omp parallel private(threadNumber, beginIndex, endIndex)
    {
        #pragma omp single
        {
            printf("\n SORTING OF EACH SUBARRAY \n");
        }
        threadNumber = omp_get_thread_num();

        if (threadNumber > effectiveThreadCount) {
            beginIndex = endIndex = -1;  // do nothing
        } else {
            if (arraySize % effectiveThreadCount == 0) {
                int localSize = static_cast<int>((
                    arraySize / effectiveThreadCount));
                beginIndex = threadNumber * localSize;
                endIndex = beginIndex + localSize - 1;
            } else {
                if (effectiveThreadCount == 1) {
                    beginIndex = 0;
                    endIndex = arraySize - 1;
                } else {
                    int localSize = static_cast<int>(
                        (arraySize / effectiveThreadCount) + 1);
                    beginIndex = threadNumber * localSize;
                    if (threadNumber == effectiveThreadCount - 1) {
                        endIndex = arraySize - 1;
                    } else {
                        endIndex = beginIndex + localSize - 1;
                    }
                }
            }
        }

        bitwiseSort(array + beginIndex, endIndex - beginIndex + 1);
        bool sortedLocally = checkAscending(
            array + beginIndex, endIndex - beginIndex + 1);
        #pragma omp critical
        {
            allSubarraysSortedCorrectly &= sortedLocally;
            printf("\n ------------- \nThreadNumber: %i\t\t"
            "begin: %i\tend: %i\nARRAY {", threadNumber, beginIndex, endIndex);
            for (int i = beginIndex; i <= endIndex; i++) {
                printf("%i\t", array[i]);
            }
            printf((sortedLocally ? "}\n SORTED CORRECTLY \n" :
            "}\n SORTED NOT CORRECTLY \n"));
        }
        #pragma omp barrier
        #pragma omp single
        {
            printf(allSubarraysSortedCorrectly ?
            "\n ARRAYS SORTED CORRECTLY \n"
            : "\n ARRAYS SORTED NOT CORRECTLY \n");
            NetworkBuilder nb;
            nb.setNetworkSize(effectiveThreadCount);
            parallelArray = nb.getParallelBlockArray();
        }
    }
    return allSubarraysSortedCorrectly;
}
