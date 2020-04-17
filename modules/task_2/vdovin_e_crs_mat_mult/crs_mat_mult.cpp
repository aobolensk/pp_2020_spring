// Copyright 2020 Vdovin Eugene
#include <vector>
#include <complex>
#include <algorithm>
#include <utility>
#include <cmath>
#include "../../../modules/task_2/vdovin_e_crs_mat_mult/crs_mat_mult.h"

CRSMatrix::CRSMatrix(const int n_, const int nz_,
    const std::vector<std::complex<double>> &value_,
    const std::vector<int> col_,
    const std::vector<int> rowindex_) {
        n = n_;
        nz = nz_;
        value = value_;
        col = col_;
        rowindex = rowindex_;
        omp_k = 1;
    }

CRSMatrix::CRSMatrix(const int n_, const int nz_) {
    n = n_;
    nz = nz_;
    value.resize(nz);
    col.resize(nz);
    rowindex.resize(n + 1);
    omp_k = 1;
}

CRSMatrix::CRSMatrix(const CRSMatrix& mtx) {
    n = mtx.n;
    nz = mtx.nz;
    value = mtx.value;
    col = mtx.col;
    rowindex = mtx.rowindex;
    omp_k = 1;
}

CRSMatrix& CRSMatrix::operator=(const CRSMatrix &mtx) {
    n = mtx.n;
    nz = mtx.nz;
    value = mtx.value;
    col = mtx.col;
    rowindex = mtx.rowindex;
    omp_k = 1;
    return *this;
}

CRSMatrix CRSMatrix::operator*(const CRSMatrix &mtx) const {
    if (nz >= mtx.nz) {
        CRSMatrix res = multiplicate(mtx.transpose());
        return res;
    } else {
        CRSMatrix rest = mtx.multiplicate((*this).transpose());
        return rest.transpose();
    }
}

CRSMatrix CRSMatrix::transpose() const {
    CRSMatrix at(n, nz);

    for (int i = 0; i < nz; ++i) {
        at.rowindex[col[i] + 1]++;
    }

    int s = 0;
    for (int i = 1; i <= n; ++i) {
        int tmp = at.rowindex[i];
        at.rowindex[i] = s;
        s = s + tmp;
    }

    for (int i = 0; i < n; ++i) {
        int j1 = rowindex[i], j2 = rowindex[i + 1];
        int c = i;

        for (int j = j1; j < j2; ++j) {
            std::complex<double> v = value[j];

            int rindex = col[j];
            int iindex = at.rowindex[rindex + 1];

            at.value[iindex] = v;
            at.col[iindex] = c;
            at.rowindex[rindex + 1]++;
        }
    }

    return at;
}

CRSMatrix CRSMatrix::multiplicate(const CRSMatrix &mtx) const {
    if (n == mtx.n) {
        std::vector<std::vector<std::complex<double>>> value_res(n);
        std::vector<std::vector<int>> col_res(n);
        std::vector<int> rownz(n + 1);

        #pragma omp parallel num_threads(omp_k)
        {
            std::vector<int> tmp(n + 1);
            int numThread = omp_get_thread_num();
            int numThreads = omp_get_num_threads();
            int delta, begin, end;

            if (numThreads > n) {
                delta = 1;
            } else {
                if (n / 2 < n % numThreads) {
                    delta = n / numThreads + 1;
                } else {
                    delta = n / numThreads;
                }
            }

            begin = numThread * delta;

            if (numThread < numThreads - 1) {
                end = (numThread + 1) * delta;
            } else {
                end = n;
            }
            for (int i = begin; i < end; ++i) {
                std::fill(tmp.begin(), tmp.end(), -1);

                int ks = rowindex[i];
                int kf = rowindex[i + 1];

                for (int m = ks; m < kf; ++m) {
                    tmp[col[m]] = m;
                }

                if (ks != kf) {
                    for (int j = 0; j < n; ++j) {
                        std::complex<double> sum(0.0, 0.0);

                        int ls = mtx.rowindex[j];
                        int lf = mtx.rowindex[j + 1];

                        for (int k = ls; k < lf; ++k) {
                            int ind = tmp[mtx.col[k]];
                            if (ind != -1) {
                                sum += value[ind] * mtx.value[k];
                            }
                        }

                        if (sqrt(sum.real() * sum.real() + sum.imag() * sum.imag()) > 0.000000001) {
                            col_res[i].push_back(j);
                            value_res[i].push_back(sum);
                            rownz[i]++;
                        }
                    }
                }
            }
        }

        int nz = 0;
        for (int i = 0; i < n; ++i) {
            int tmp = rownz[i];
            rownz[i] = nz;
            nz += tmp;
        }
        rownz[n] = nz;

        CRSMatrix res(n, nz);
        std::vector<std::complex<double>> res_val;
        std::vector<int> res_col;

        for (int i = 0; i < n; ++i) {
            int size = col_res[i].size();

            for (int j = 0; j < size; ++j) {
                res_col.push_back(col_res[i][j]);
                res_val.push_back(value_res[i][j]);
            }
        }
        res.value = res_val;
        res.col = res_col;
        res.rowindex = rownz;

        return res;
    } else {
        return *this;
    }
}

bool CRSMatrix::findElemInVector(const std::vector<std::pair<int, std::complex<double>>>& vec, const int elem) {
    for (auto& elemVec : vec) {
        if (elem == elemVec.first) {
            return true;
        }
    }
    return false;
}

void CRSMatrix::buildRandomCRSMatrix() {
    value.clear();
    col.clear();

    std::random_device rd;
    std::mt19937 mersenne(rd());

    std::vector<std::vector<std::pair<int, std::complex<double>>>> gen(n);

    for (int i = 0; i < nz; ++i) {
        int rowg, colg;

        do {
            rowg = mersenne() % n;
            colg = mersenne() % n;
        } while (findElemInVector(gen[rowg], colg));

        std::complex<double> tmp(mersenne() % 1000 + 1, mersenne() % 1000 + 1);
        gen[rowg].push_back({ colg, tmp });
    }

    int rownz = 0;
    for (int colGen = 0; colGen < n; ++colGen) {
        rowindex[colGen] = rownz;

        std::sort(gen[colGen].begin(), gen[colGen].end(),
            [](const std::pair<int, std::complex<double>>& a,
            const std::pair<int, std::complex<double>>& b) {
            return a.first < b.first;
        });

        for (auto& rowGen : gen[colGen]) {
            col.push_back(rowGen.first);
            value.push_back(rowGen.second);
            rownz++;
        }
    }
    rowindex[n] = rownz;
}

void CRSMatrix::getThreads(int numTreads) {
    omp_k = numTreads;
}

bool CRSMatrix::operator==(const CRSMatrix &mtx) const {
    if ((n == mtx.n) && (nz == mtx.nz) && (value == mtx.value) && (col == mtx.col) && (rowindex == mtx.rowindex)) {
        return true;
    } else {
        return false;
    }
}

bool CRSMatrix::operator!=(const CRSMatrix &mtx) const {
    return !(*this == mtx);
}
