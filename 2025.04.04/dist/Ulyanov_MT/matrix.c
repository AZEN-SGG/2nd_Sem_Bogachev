#include <math.h>
#include "matrix.h"

double count_r1(double* a, double* b, int n)
  {
  int i, j, u;
  double sum, sumstl, max = 0;
  if (n > 4000) return 0;
  for (j = 0; j < n; j++)
      {
      sumstl = 0;
      for (i = 0; i < n; i++)
          {
          if (i == j) sum = -1;
          else sum = 0;
          for (u = 0; u < n; u++)
              sum += a[i * n + u] * b[u * n + j];
          sumstl += fabs(sum);
          }
      if (sumstl > max) max = sumstl;
      }
  return max;
  }

double count_r2(double* a, double* b, int n)
  {
  int i, j, u;
  double sum, sumstl, max = 0;
  if (n > 4000) return 0;
  for (j = 0; j < n; j++)
      {
      sumstl = 0;
      for (i = 0; i < n; i++)
          {
          if (i == j) sum = -1;
          else sum = 0;
          for (u = 0; u < n; u++)
              sum += b[i * n + u] * a[u * n + j];
          sumstl += fabs(sum);
          }
      if (sumstl > max) max = sumstl;
      }
  return max;
  }
  
double count_norm(double* a, int n)
  {
  int i, j;
  double max = 0, sum;
  for (i = 0; i < n; i++)
      {
      sum = 0;
      for (j = 0; j < n; j++) sum += fabs(a[i * n + j]);
      if (sum > max) max = sum;
      }
  return max;
  }
  
int is_null(double a, double norm)
  {
  if (fabs(a) <= EPS * norm) return 1;
  return 0;
  }
