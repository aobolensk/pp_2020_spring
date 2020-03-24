// Copyright 2020 Vdovin Eugene
#include <vector>
#include <complex>
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
    }

CRSMatrix::CRSMatrix(const CRSMatrix& mtx) {
    n = mtx.n;
    nz = mtx.nz;
    value = mtx.value;
    col = mtx.col;
    rowindex = mtx.rowindex;
}

CRSMatrix& CRSMatrix::operator=(const CRSMatrix &mtx) {
    n = mtx.n;
    nz = mtx.nz;
    value = mtx.value;
    col = mtx.col;
    rowindex = mtx.rowindex;
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
        std::vector<std::complex<double>> *value_res = new std::vector<std::complex<double>>[n];
        std::vector<int> *col_res = new std::vector<int>[n];
        int *rownz = new int[n + 1];
        std::fill(rownz, rownz + n, 0);

        #pragma omp parallel {
            std::vector<int> tmp(n + 1);
            #pragma omp for schedule(static)
                for (int i = 0; i < n; ++i) {
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

        for (int i = 0; i < n; ++i) {
            int size = col_res[i].size();

            for (int j = 0; j < size; ++j) {
                res.col.push_back(col_res[i][j]);
                res.value.push_back(value_res[i][j]);
            }
        }
        res.rowindex = rownz;

        delete[] value_res;
        delete[] col_res;
        delete[] rownz;

        return res;
    } else {
        return *this;
    }
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
