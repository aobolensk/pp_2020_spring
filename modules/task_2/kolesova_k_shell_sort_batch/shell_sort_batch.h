
#include <vector>

std::vector<int> randVec(int size);
std::vector<int> sortShell(std::vector<int>& vec, int l, int r);
std::vector<int> oneShellBetchSort(std::vector<int>& vec);
std::vector<int> shuffle(std::vector<int>& vec, int l, int r);
std::vector<int> unshuffle(std::vector<int>& vec, int l, int r);

std::vector<int> shellBetchSort_omp(std::vector<int>& vec);
