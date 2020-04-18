// Copyright 2020 Silenko Dmitrii

#include <iostream>
#include <random>
#include <ctime>
#include <numeric>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "../../../modules/task_2/silenko_d_convex_binary_omp/convex_binary_omp.h"

int** getRandomMas(const int n, const int m) {
  if (n <= 0) {
    throw "Wrong rows";
  } else if (m <= 0) {
    throw "wrong columns";
  }
  int** mas = new int*[n];
  std::mt19937 seed(n);
  std::uniform_real_distribution<> rnd(0, 200);
  for (int i = 0; i < n; i++)
    mas[i] = new int[m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      mas[i][j] = static_cast<int>(rnd(seed)) % 2;
    }
  }
  return mas;
}

double length(int* p1, int* p2) {
  return(sqrt((p2[0] - p1[0])*(p2[0] - p1[0]) + (p2[1] - p1[1])*(p2[1] - p1[1])));
}

double cosvec(int* p1, int* p2, int* p3) {
  double ax = p2[0] - p1[0];
  double ay = p2[1] - p1[1];
  double bx = p3[0] - p1[0];
  double by = p3[1] - p1[1];
  return ((ax*bx + ay * by) / (sqrt(ax*ax + ay * ay) * sqrt(bx*bx + by * by)));
}

std::vector<int*> Jarvis(int** convex_mas, int n) {
  std::vector<int*> res;
  if (n == 1) {
    res.push_back(convex_mas[0]);
  } else if (n == 2) {
    res.push_back(convex_mas[0]);
    res.push_back(convex_mas[1]);
  } else {
    int m = 0;

    res.push_back(convex_mas[m]);

    int* last = new int[2];
    int* beforelast = new int[2];
    last = convex_mas[m];
    beforelast[0] = convex_mas[m][0] - 2;
    beforelast[1] = convex_mas[m][1];

    double mincos, cos;
    int minind = 0;
    double maxlen = 0;
    while (1) {
      mincos = 2;
      for (int i = 0; i < n; i++) {
        cos = round(cosvec(last, beforelast, convex_mas[i]) * 10000000) / 10000000;
        if (cos < mincos) {
          minind = i;
          mincos = cos;
          maxlen = length(last, convex_mas[i]);
        } else {
          if (cos == mincos) {
            double len = length(last, convex_mas[i]);
            if (len > maxlen) {
              minind = i;
              maxlen = len;
            }
          }
        }
      }

      beforelast = last;
      last = convex_mas[minind];
      if (last == convex_mas[m])
        break;
      res.push_back(convex_mas[minind]);
    }
  }
  return res;
}

std::vector<int*> getComponent(int** mas, int n, int m, int** *convex_mas, int *num) {
  *num = 0;
  int kn = 0, km = 0, cur = 1;
  int A, B, C;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      kn = j - 1;
      if (kn+1 <= 0) {
        kn = 1;
        B = 0;
      } else {
        B = mas[i][kn];
      }
      km = i - 1;
      if (km+1 <= 0) {
        km = 1;
        C = 0;
      } else {
        C = mas[km][j];
      }
      A = mas[i][j];

      if (A == 0) {
      } else {
        *num = *num + 1;
        if (B == 0 && C == 0) {
          cur++;
          mas[i][j] = cur;
        }
        if (B != 0 && C == 0) {
          mas[i][j] = B;
        }
        if (B == 0 && C != 0) {
          mas[i][j] = C;
        }
        if (B != 0 && C != 0) {
          if (B == C) {
            mas[i][j] = B;
          } else {
            mas[i][j] = B;
            for (int k = 0; k < i; k++)
              for (int kk = 0; kk < m; kk++)
                if (mas[k][kk] == C)
                  mas[k][kk] = B;
          }
        }
      }
    }

  (*convex_mas) = new int*[*num];
  for (int i = 0; i < *num; i++)
    (*convex_mas)[i] = new int[3];

  int tmp = 0;
  for (int i =0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (mas[i][j] != 0) {
        (*convex_mas)[tmp][0] = j;
        (*convex_mas)[tmp][1] = i;
        (*convex_mas)[tmp][2] = mas[i][j];
        tmp++;
      }
    }

  std::vector<int*> res;

  res = Jarvis(*convex_mas, *num);
  return res;
}

std::vector<int*> Inside(std::vector<int*> hull, int** convex_mas, int n) {
  std::vector<int*> res;
  std::vector<int> err;
  std::vector<int> cur;

  int s = hull.size();
  for (int i = 0; i < s; i++) {
    int* tmp = hull[i];
    cur.push_back(tmp[2]);
  }

  for (int i = 0; i < n; i++) {
    auto result1 = std::find(cur.begin(), cur.end(), convex_mas[i][2]);
    auto result2 = std::find(err.begin(), err.end(), convex_mas[i][2]);
    if (result2 != err.end()) {
      continue;
    } else {
      if (result1 != cur.end()) {
        res.push_back(convex_mas[i]);
        int* tmp = convex_mas[i];
        err.push_back(tmp[2]);
      }
    }
  }
  return res;
}

std::vector<int*> Jarvis_OMP(int** convex_mas, int n, int num_thr) {
  std::vector<int*> res;
  std::vector<std::vector<int*>> local_res(num_thr);
  if (n == 1) {
    res.push_back(convex_mas[0]);
  } else if (n == 2) {
    res.push_back(convex_mas[0]);
    if (convex_mas[0] != convex_mas[1])
      res.push_back(convex_mas[1]);
  } else {
    int m = 0;

    res.push_back(convex_mas[m]);
    for (int i = 0; i < num_thr; i++)
      local_res[i].push_back(convex_mas[m]);

    int* last;
    int* beforelast;


    double mincos, cos;
    int minind = 0;
    double maxlen = 0;
    int id, delta, ost;
    double len;

#pragma omp parallel private(id, delta, ost, mincos, cos, minind, maxlen, last, beforelast, len) num_threads(num_thr)
    {
      delta = n / num_thr;
      id = omp_get_thread_num();

      if (id == num_thr - 1) {
        ost = n % num_thr;
      } else {
        ost = 0;
      }

      maxlen = 0;
      minind = 0;
      last = new int[2];
      beforelast = new int[2];
      last = convex_mas[m];
      beforelast[0] = convex_mas[m][0] - 2;
      beforelast[1] = convex_mas[m][1];

      while (1) {
        mincos = 2;
        for (int i = id * delta; i < id * delta + delta + ost; i++) {
          cos = round(cosvec(last, beforelast, convex_mas[i]) * 10000000) / 10000000;
          if (cos < mincos) {
            minind = i;
            mincos = cos;
            maxlen = length(last, convex_mas[i]);
          } else if (cos == mincos) {
            len = length(last, convex_mas[i]);
            if (len > maxlen) {
              minind = i;
              maxlen = len;
            }
          }
        }

        if (id != 0) {
          cos = round(cosvec(last, beforelast, convex_mas[0]) * 10000000) / 10000000;
          if (cos < mincos) {
            minind = 0;
            mincos = cos;
            maxlen = length(last, convex_mas[0]);
          } else if (cos == mincos) {
            len = length(last, convex_mas[0]);
            if (len > maxlen) {
              minind = 0;
              maxlen = len;
            }
          }
        }

        beforelast = last;
        last = convex_mas[minind];
        if (last == convex_mas[m])
          break;
        local_res[id].push_back(convex_mas[minind]);
      }
    }

    std::vector<int*> finale_local;
    for (int i = 0; i < num_thr; i++) {
      int size = local_res[i].size();
      for (int j = 0; j < size; j++)
        finale_local.push_back(local_res[i][j]);
    }


    int s = finale_local.size();

    last = new int[2];
    beforelast = new int[2];
    last = convex_mas[m];
    beforelast[0] = convex_mas[m][0] - 2;
    beforelast[1] = convex_mas[m][1];
    while (1) {
      mincos = 2;
      for (int i = 0; i < s; i++) {
        cos = round(cosvec(last, beforelast, finale_local[i]) * 10000000) / 10000000;
        if (cos < mincos) {
          minind = i;
          mincos = cos;
          maxlen = length(last, finale_local[i]);
        } else if (cos == mincos) {
          double len = length(last, finale_local[i]);
          if (len > maxlen) {
            minind = i;
            maxlen = len;
          }
        }
      }

      beforelast = last;
      last = finale_local[minind];
      if (last == finale_local[m])
        break;
      res.push_back(finale_local[minind]);
    }
  }
  return res;
}


std::vector<int*> getComponent_OMP(int** mas, int n, int m, int** *convex_mas, int *num, int num_thr) {
  *num = 0;
  int kn = 0, km = 0, cur = 1;
  int A, B, C;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      kn = j - 1;
      if (kn + 1 <= 0) {
        kn = 1;
        B = 0;
      } else {
        B = mas[i][kn];
      }
      km = i - 1;
      if (km + 1 <= 0) {
        km = 1;
        C = 0;
      } else {
        C = mas[km][j];
      }
      A = mas[i][j];

      if (A == 0) {
      } else {
        *num = *num + 1;
        if (B == 0 && C == 0) {
          cur++;
          mas[i][j] = cur;
        }
        if (B != 0 && C == 0) {
          mas[i][j] = B;
        }
        if (B == 0 && C != 0) {
          mas[i][j] = C;
        }
        if (B != 0 && C != 0) {
          if (B == C) {
            mas[i][j] = B;
          } else {
            mas[i][j] = B;
            int k;
#pragma omp parallel private(k) num_threads(num_thr)
            {
#pragma omp for
              for (k = 0; k < i; k++)
                for (int kk = 0; kk < m; kk++)
                  if (mas[k][kk] == C)
                    mas[k][kk] = B;
            }
          }
        }
      }
    }

  (*convex_mas) = new int*[*num];
  for (int i = 0; i < *num; i++)
    (*convex_mas)[i] = new int[3];

  int tmp = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (mas[i][j] != 0) {
        (*convex_mas)[tmp][0] = j;
        (*convex_mas)[tmp][1] = i;
        (*convex_mas)[tmp][2] = mas[i][j];
        tmp++;
      }
    }

  std::vector<int*> res;
  res = Jarvis_OMP(*convex_mas, *num, num_thr);
  return res;
}
