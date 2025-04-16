#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "functions.h"

io_status solve4(double*, double*, double, int, double*);

int main(int argc, char* argv[])
  {
  int task = 4;
  io_status ret;
  double* x;
  double* yd;
  int n;
  double x0;
  char* name = 0;
  double res;
  double t;
  if (!((argc == 4) && sscanf(argv[1], "%le", &x0) == 1 && sscanf(argv[2], "%d", &n) == 1))
      {
      printf("Usage: %s x0 n file\n", argv[0]);
      return 1;
      }
  name = argv[3];
  x = (double*) malloc(n * sizeof(double));
  yd = (double*) malloc(2 * n * sizeof(double));
  if ((!x) || (!yd))
      {
      printf("Not enough memory\n");
      if (x) free(x);
      if (yd) free(yd);
      return 2;
      }
  ret = read_func_diff(x, yd, n, name);
  if (ret != SUCCESS)
      {
      switch(ret)
          {
          case ERROR_OPEN:
              printf("Can not open file %s\n", name);
              break;
          case ERROR_READ:
              printf("Can not read file %s\n", name);
              break;
          default:
              printf("UNknown error in file %s\n", name);
          }
      free(x);
      free(yd);
      return 3;
      }
  t = clock();
  ret = solve4(x, yd, x0, n, &res);
  t = (clock() - t) / CLOCKS_PER_SEC;
  if (ret != SUCCESS)
      {
      printf("Similar points in file %s\n", name);
      free(x);
      free(yd);
      return 4;
      }
  printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], task, res, t);
  free(x);
  free(yd);
  return 0;
  }
    
io_status solve4(double* x, double* yd, double x0, int n, double* res)
  {
  int i, j;
  double el_n, el_prev, sum = 0;
  for (i = n - 1; i > 0; i--)
      {
      el_n = x[i];
      el_prev = x[i - 1];
      if (equal(el_n, el_prev)) return ERROR_FUNCTION;
      yd[2 * i] = (yd[2 * i] - yd[2 * i - 2]) / (el_n - el_prev);
      }
  for (j = 1; j < 2 * n; j++)
      {
      for (i = 2 * n - 1; i > j; i--)
          {
          el_n = x[i / 2];
          el_prev = x[(i - j - 1) / 2];
          if (equal(el_n, el_prev)) return ERROR_FUNCTION;
          yd[i] = (yd[i] - yd[i - 1]) / (el_n - el_prev);
          }
      }
  for (i = 2 * n - 1; i >= 0; i--)
      {
      sum = yd[i] + (x0 - x[i / 2]) * sum;
      }
  *res = sum;
  return SUCCESS;
  }
