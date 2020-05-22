// Copyright 2020 Gaydaychuk Yury
#include <tbb/tbb.h>
#include <random>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include <functional>
#include <numeric>
#include "../../../modules/task_3/gaydaychuk_bitwise_oddeven_sort/bitwise_oddeven_sort.h"

class Hello {
    int phase;
 public:
    explicit Hello(int _i) : phase(_i) {}
    void operator()(const tbb::blocked_range<int>& r) const {
        int begin = r.begin(),  end = r.end();
        for (int i = begin; i != end; i++) {
            printf("\n hello from me = %i-th unit --- %i\n", i, phase);
        }
    }
};

tbb::task* HelloTask::execute() {
    for (int jj = 0; jj <= i; jj++) {
        printf("\n params: i = %i, jj = %i\t\t\t j = %i\n", i, jj, j);
    }
    return NULL;
}

tbb::task* SortSubarrayTask::execute() {
    getLocalArea(taskId, taskCount, size,
        &bI, &eI);
    bitwiseSort(array + bI, eI - bI + 1);
    // bool res = checkAscending(array + bI, eI - bI + 1);
    // printf("\n task: %i\t sorted %s\n", taskId, (res ? "good" : "bad"));
    return NULL;
}

tbb::task* MergeSubarraysTask::execute() {
    mergeAndSplit(array1, size1, array2, size2);
    // printf("\nmerged pair \n");

    return NULL;
}

std::vector<int> getRandomVector(int sz) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}
bool checkAscending(int *p, int length) {
    return std::is_sorted(p, p + length);
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
void bitwiseSort(int *p, int length, double *time) {
    tbb::tick_count t0;
    if (time != nullptr) {
        t0 = tbb::tick_count::now();
    }
    int max = getMax(p, length);
    for (int digit = 1; max / digit > 0; digit *= 10) {
        sortByDigit(p, length, digit);
    }
    if (time != nullptr) {
        tbb::tick_count t1 = tbb::tick_count::now();
        *time = (t1 - t0).seconds();
    }
}
void tbbHello(int i) {
    parallel_for(tbb::blocked_range<int>(1, 10, 1), Hello(i));
}

void parallelLocalSort(int *p, int length, int chunksCount, double *time) {
    tbb::tick_count t0;
    if (time != nullptr) {
        t0 = tbb::tick_count::now();
    }
    // getVirtualThreadsCount
    int effectiveChunksCount = getEffectiveUnitCount(
        length, chunksCount);
    // local sort
    tbb::task_list subSortingTaskList;
    for (int i = 0; i < effectiveChunksCount; i++) {
        SortSubarrayTask *pat = new(tbb::task::allocate_root())
            SortSubarrayTask(p, i, effectiveChunksCount, length);
        subSortingTaskList.push_back(*pat);
    }

    tbb::task::spawn_root_and_wait(subSortingTaskList);

    // create network
    NetworkBuilder nb;
    nb.setNetworkSize(effectiveChunksCount);
    std::list<std::vector<std::pair <int, int> > > parallelArray =
        nb.getParallelBlockArray();


    // merge
    for (auto itBlocks = parallelArray.begin();
        itBlocks != parallelArray.end();
        ++itBlocks) {
        // prepare merging
        tbb::task_list mergingTaskList;

        int parallelblockSize = static_cast<int>((itBlocks->size()));
        int sa1 = 0, sa2 = 0;
        int bI1 = 0, eI1 = 0;
        int bI2 = 0, eI2 = 0;
        for (int i = 0; i < parallelblockSize; ++i) {
            bI1 = 0, eI1 = 0;
            bI2 = 0, eI2 = 0;
            sa1 = itBlocks->at(i).first;
            sa2 = itBlocks->at(i).second;
            // get areas to merge
            if (length % effectiveChunksCount == 0) {
                int localSize = static_cast<int>((
                    length / effectiveChunksCount));
                bI1 = sa1 * localSize;
                bI2 = sa2 * localSize;

                eI1 = bI1 + localSize - 1;
                eI2 = bI2 + localSize - 1;

            } else {
                if (effectiveChunksCount != 1) {
                    int localSize = static_cast<int>((
                        length / effectiveChunksCount) + 1);
                    bI1 = sa1 * localSize;
                    bI2 = sa2 * localSize;

                    if (sa1 == effectiveChunksCount - 1) {
                        eI1 = length - 1;
                    } else {
                        eI1 = bI1 + localSize - 1;
                    }
                    if (sa2 == effectiveChunksCount - 1) {
                        eI2 = length - 1;
                    } else {
                        eI2 = bI2 + localSize - 1;
                    }
                }
            }
            MergeSubarraysTask *mst = new(tbb::task::allocate_root())
                MergeSubarraysTask(p + bI1, eI1 - bI1 + 1,
                    p + bI2, eI2 - bI2 + 1);
            mergingTaskList.push_back(*mst);
            // execute
            tbb::task::spawn_root_and_wait(mergingTaskList);
            // // merge
            // mergeAndSplit(array + bI1, eI1 - bI1 + 1,
            //     array + bI2, eI2 - bI2 + 1);
        }
    }
    // endofmerge
    if (time != nullptr) {
        tbb::tick_count t1 = tbb::tick_count::now();
        *time = (t1 - t0).seconds();
    }
}

int getEffectiveUnitCount(int arraySize, int maxThreadCount,
    int minimalSubarrayLength) {
    int effectiveThreadCount = 0;
    if (arraySize < minimalSubarrayLength * maxThreadCount) {
        if (arraySize % minimalSubarrayLength == 0) {
            effectiveThreadCount = static_cast<int>((
                arraySize / minimalSubarrayLength));
        } else {
            effectiveThreadCount = static_cast<int>((
                arraySize / minimalSubarrayLength) + 1);
        }
    } else {
        if (arraySize < (minimalSubarrayLength + 1) *
        (maxThreadCount - 1) + 1) {
            effectiveThreadCount = maxThreadCount - 1;
        } else {
            effectiveThreadCount = maxThreadCount;
        }
    }
    return effectiveThreadCount;
}

void getLocalArea(
    int threadNumber, int effectiveThreadCount,
    int arraySize,
    int *beginIndex, int *endIndex) {
    if (threadNumber > effectiveThreadCount) {
        *beginIndex = *endIndex = -1;  // do nothing
    } else {
        if (arraySize % effectiveThreadCount == 0) {
            int localSize = static_cast<int>(
                arraySize / effectiveThreadCount);
            *beginIndex = threadNumber * localSize;
            *endIndex = *beginIndex + localSize - 1;
        } else {
            if (effectiveThreadCount == 1) {
                *beginIndex = 0;
                *endIndex = arraySize - 1;
            } else {
                int localSize = static_cast<int>(
                    (arraySize / effectiveThreadCount) + 1);
                *beginIndex = threadNumber * localSize;
                if (threadNumber == effectiveThreadCount - 1) {
                    *endIndex = arraySize - 1;
                } else {
                    *endIndex = *beginIndex + localSize - 1;
                }
            }
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
    pseudoSort(0, static_cast<int>(indexArray.size()));
}

void NetworkBuilder::pseudoSort(int lo, int n) {
    if (n > 1) {
        int m = n / 2;
        pseudoSort(lo, m);
        pseudoSort(lo + m, m);
        bMerge(lo, n, 1);
    }
}

void NetworkBuilder::bMerge(int lo, int n, int r) {
    // lo is the starting position and
    // n is the length of the piece to be merged,
    // r is the distance of the elements to be compared
    int m = r * 2;
    if (m < n) {
        bMerge(lo, n, m);      // even subsequence
        bMerge(lo + r, n, m);    // odd subsequence
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
