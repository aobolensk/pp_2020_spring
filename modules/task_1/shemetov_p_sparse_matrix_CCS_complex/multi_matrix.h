// Copyright 2020 Shemetov Philipp

#ifndef MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CCS_COMPLEX_MULTI_MATRIX_H_
#define MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CCS_COMPLEX_MULTI_MATRIX_H_

#include <vector>
#include <complex>

typedef std::vector<std::vector<std::complex<double>>> mtxComplex;

class SparseMatrixCCS {
 private :
    std::vector<std::complex<double>> value;
    std::vector<int> row_index;
    std::vector<int> col_offsets;
    size_t n, m;
 public :
    SparseMatrixCCS(size_t _m, size_t _n);
    SparseMatrixCCS(size_t m, size_t n, size_t nonezero);

    SparseMatrixCCS(size_t m, size_t n, double sparseness);

    SparseMatrixCCS(size_t _m, size_t _n,
                  std::vector<std::complex<double>> _value,
                  std::vector<int> _row_index,
                  std::vector<int> _col_offsets);

    explicit SparseMatrixCCS(const mtxComplex &mt);

    SparseMatrixCCS(const SparseMatrixCCS &obj);

    static SparseMatrixCCS MultiplySparseMatrix(const SparseMatrixCCS& A,
                                                const SparseMatrixCCS& B);

    bool operator==(const SparseMatrixCCS &) const;

    // void PrintCCS();

    SparseMatrixCCS transpose();
};



// void Print(const mtxComplex &);

mtxComplex multiMatrix(const mtxComplex &mtxA, const mtxComplex &mtxB);



#endif  //  MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CCS_COMPLEX_MULTI_MATRIX_H_
