#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "matrix.h"

io_status read_matrix(double* a, int n, int m, const char* name)
  {
  int i, j;
  FILE* fp;
  if (!(fp = fopen(name, "r")))
      return ERROR_OPEN;
  for (i = 0; i < n; i++)
      {
      for (j = 0; j < m; j++)
          {
          if (fscanf(fp, "%lf", a + i * m + j) != 1)
              {
              fclose(fp);
              return ERROR_READ;
              }
          }
      }
  fclose(fp);
  return SUCCESS;
  }
  
void print_matrix(const double* a, int n, int m, int p)
  {
  int np = (n > p ? p : n);
  int mp = (m > p ? p : m);
  int i, j;
  for (i = 0; i < np; i++)
      {
      for (j = 0; j < mp; j++)
          printf(" %10.3e", a[i * m + j]);
      printf("\n");
      }
  }
  
void init_matrix(double* a, int n, int m, int k)
  {
  int i, j;
  for (i = 0; i < n; i++)
      {
      for (j = 0; j < m; j++)
          a[i * m + j] = f(k, n, m, i+1, j+1);
      }
  }
  
double f(int k, int n, int m, int i, int j)
  {
  switch (k)
      {
      case 1: return (n >= m ? n : m) - (i >= j ? i : j) + 1;
      case 2: return (i >= j ? i : j);
      case 3: return (i - j >= 0 ? i - j : j - i);
      case 4: return 1./(i + j - 1);
      }
  return -1e308;
  }
  
void init_vector(double* b, double* a, int n)
  {
  int i, k;
  double sum;
  for (i = 0; i < n; i++)
      {
      sum = 0;
      for (k = 1; k < n; k += 2) sum += a[i * n + k];
      b[i] = sum;
      }
  }
