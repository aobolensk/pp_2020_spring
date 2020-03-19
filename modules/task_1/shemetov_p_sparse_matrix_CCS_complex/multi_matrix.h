#ifndef MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CSS_COMPLEX_MULTI_MATRIX_H_
#define MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CSS_COMPLEX_MULTI_MATRIX_H_
#include <vector>
#include <complex>


class SparseMatrixCCS
{
private:
    std::vector<std::complex<int>> value;
    std::vector<int> row_index;
    std::vector<int> col_offsets;
    int n, m, noneZero;
public:
    SparseMatrixCCS(int n, int m, int noneZero);
    SparseMatrixCCS(const SparseMatrixCCS& obj);
    SparseMatrixCCS randomGenerateMatrix(int n, int m);
    SparseMatrixCCS TransposeMatrix();
    void Print();
    ~SparseMatrixCCS();
};



#endif // MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CSS_COMPLEX_MULTI_MATRIX_H_