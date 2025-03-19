#include "solve.h"
#include <math.h>

#define eps 1e-17

int t8_solve(double* a, int m, int n)
  {
  int i, j, k, ind_max_i = 0, ind_max_j = 0;
  double sumstr = 0, sum, max = 0;
  int l = 0;
  if ((m == 0) || (n == 0)) return 0;
  for (i = 0; i < m; i++)
      {
      sumstr = 0;
      for (j = 0; j < n; j++) sumstr += fabs(a[i * n + j]);
      for (j = 0; j < n; j++)
          {
          sum = sumstr;
          for (k = 0; k < m; k++)
              {
              if (k == i) sum -= fabs(a[k * n + j]);
              else sum += fabs(a[k * n + j]);
              }
          if (sum > max)
              {
              max = sum;
              ind_max_i = i;
              ind_max_j = j;
              }
          }
      }
  for (i = 0; i < m; i++)
      {
      for (j = 0; j < n; j++)
          {
          if ((j != ind_max_j) && (i != ind_max_i))
              {
              a[l] = a[i * n + j];
              l++;
              }
          }
      }
  return ind_max_i * n + ind_max_j;
  }
