// Copyright 2020 Karin Timofey
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include <complex>
#include <algorithm>
#include "../../../modules/task_1/karin_t_sparce_matrix_complex_CCS/sparce_matrix.h"

SparceMatrix::SparceMatrix(int _nCol, int _nRow, int not_null_count) {
  if (_nCol <= 0 || _nRow <= 0 || not_null_count < 0)
    throw "negative size";
  if (_nCol * _nRow < not_null_count)
    throw "not null count does'n match the size";
  nCol = _nCol;
  nRow = _nRow;
  point.resize(nCol);
  std::mt19937 ran;
  ran.seed(static_cast<unsigned int>(time(0)));
  unsigned count = not_null_count;
  for (int i = 0; i < nCol; i++) {
    unsigned randnum = ran() % nRow;
    int next = std::min(count, randnum);
    count -= next;
    point[i] = next;
  }
  while (count != 0) {
    for (int i = 0; i < nCol; i++) {
      if (point[i] < nRow) {
        point[i]++;
        count--;
      }
      if (count == 0)
        break;
    }
  }
  std::random_shuffle(point.begin(), point.end());
  for (int i=0; i < nCol-1; i++) {
     point[i+1] += point[i];
  }

  for (int i = 0; i < nCol; i++) {
    int k;
    if (i == 0)
      k = point[i];
    else if (i == nCol - 1)
      k = not_null_count - point[i - 1];
    else
      k = point[i]-point[i-1];
    std::vector<int> col;
    for (int j = 0; j < k; j++) {
      int r = ran()%nRow;
      bool added = false;
      while (added == false) {
        bool exist = false;
        for (unsigned i = 0; i < col.size(); i++) {
          if (col[i] == r) {
            exist = true;
            break;
          }
        }
        if (exist == false) {
          col.push_back(r);
          added = true;
        } else {
          r = (r+1)%nRow;
        }
      }
    }
    std::sort(col.begin(), col.end());
    for (int i = 0; i < k; i++)
      row_number.push_back(col[i]);
  }

  for (int i = 0; i < not_null_count; i++) {
    val.push_back(std::complex<int>(ran() % 1000, ran() % 1000));
  }
}

SparceMatrix::SparceMatrix(std::vector<std::vector<std::complex<int>>> matr) {
  for (unsigned i = 0; i < matr.size()-1; i++)
    if (matr[i].size() != matr[i+1].size())
      throw "incorrect matrix";
  nRow = matr.size();
  nCol = matr[0].size();
  for (int j = 0; j < nCol; j++) {
    for (int i = 0; i < nRow; i++) {
      if (matr[i][j] != std::complex<int>(0, 0)) {
        val.push_back(matr[i][j]);
        row_number.push_back(i);
      }
    }
    point.resize(nCol);
    point[j] = val.size();
  }
}

SparceMatrix::SparceMatrix(int _nCol, int _nRow, std::vector<std::complex<int>> _val,
                            std::vector<int> _row_number, std::vector<int> _point) {
  val = _val;
  row_number = _row_number;
  point = _point;
  nCol = _nCol;
  nRow = _nRow;
}

SparceMatrix SparceMatrix::Transpose() {
  SparceMatrix Tr(this->nRow, this->nCol);
  std::vector<std::vector<int>> matr(nRow);
  std::vector<int> cols;
  int iter = 0;
  for (unsigned i = 0; i < row_number.size(); i++) {
    while ((static_cast<int>(i) >= point[iter]) && (iter != nCol-1))
      iter++;
    matr[row_number[i]].push_back(i);
    cols.push_back(iter);
  }
  Tr.point[0] = matr[0].size();
  for (int i = 1; i < nRow; i++)
    Tr.point[i] = Tr.point[i-1] + matr[i].size();
  for (int i = 0; i < nRow; i++)
    for (unsigned j = 0; j < matr[i].size(); j++) {
      Tr.val.push_back(val[matr[i][j]]);
      Tr.row_number.push_back(cols[matr[i][j]]);
    }
  return Tr;
}

SparceMatrix SparceMatrix::operator*(const SparceMatrix& B) {
  if (this->nRow != B.nCol)
    throw "wrong matrix size";
  SparceMatrix ATr = this->Transpose();
  SparceMatrix Res(B.nCol, this->nRow);
  for (int i = 0; i < B.nCol; i++) {
    for (int j = 0; j < ATr.nCol; j++) {
      std::complex<int> sum = ScalarMult(ATr, j, B, i);
      if (sum != 0) {
        Res.val.push_back(sum);
        Res.row_number.push_back(j);
      }
    }
    Res.point[i] = Res.val.size();
  }
  return Res;
}


int SparceMatrix::colCount(int col) {
  if (col == 0)
    return point[0];
  else if (col == nCol - 1)
    return val.size() - point[nCol-2];
  else
    return point[col] - point[col - 1];
}

std::complex<int> ScalarMult(const SparceMatrix& A, int i, const SparceMatrix& B, int j) {
  int k1, k2;
  if (i == 0)
    k1 = 0;
  else
    k1 = A.point[i - 1];
  if (j == 0)
    k2 = 0;
  else
    k2 = B.point[j - 1];

  std::complex<int> sum = 0;

  int stop1, stop2;
  if (i == A.nCol - 1)
    stop1 = A.val.size();
  else
    stop1 = A.point[i];
  if (j == B.nCol - 1)
    stop2 = B.val.size();
  else
    stop2 = B.point[j];
  while (k1 < stop1 && k2 < stop2) {
    if (A.row_number[k1] == B.row_number[k2]) {
      sum += A.val[k1] * B.val[k2];
      k1++;
      k2++;
    } else if (A.row_number[k1] > B.row_number[k2]) {
      k2++;
    } else {
      k1++;
    }
  }
  return sum;
}

void SparceMatrix::Print() {
  std::cout << "val: ";
  for (unsigned i = 0; i < val.size(); i++)
    std::cout << val[i] << ", ";
  std::cout << std::endl << std::endl << "row_number: ";
  for (unsigned i = 0; i < row_number.size(); i++)
    std::cout << row_number[i] << ", ";
  std::cout << std::endl << std::endl << "point: ";
  for (unsigned i = 0; i < point.size(); i++)
    std::cout << point[i] << ", ";
  std::cout << std::endl << std::endl;
  SparceMatrix B = this->Transpose();
  int iter = 0;
  for (int i = 0; i < B.nCol; i++) {
    int k;
    if (i == 0)
      k = B.point[0];
    else if (i == B.nCol - 1)
      k = B.val.size();
    else
      k = B.point[i];
    for (int i = 0; i < B.nRow; i++) {
      bool exist = false;
      if (iter < k) {
        if (B.row_number[iter] == i) {
          std::cout << B.val[iter] << "\t";
          iter++;
          exist = true;
        }
      }
      if (exist == false)
        std::cout << "0\t\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
