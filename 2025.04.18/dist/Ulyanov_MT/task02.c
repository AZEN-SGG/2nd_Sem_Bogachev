#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "functions.h"

io_status solve2(double*, double*, double, int, double*);

int main(int argc, char* argv[])
  {
  int task = 2;
  io_status ret;
  double* x;
  double* y;
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
  y = (double*) malloc(n * sizeof(double));
  if ((!x) || (!y))
      {
      printf("Not enough memory\n");
      if (x) free(x);
      if (y) free(y);
      return 2;
      }
  ret = read_function(x, y, n, name);
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
      free(y);
      return 3;
      }
  t = clock();
  ret = solve2(x, y, x0, n, &res);
  t = (clock() - t) / CLOCKS_PER_SEC;
  if (ret != SUCCESS)
      {
      printf("Similar points in file %s\n", name);
      free(x);
      free(y);
      return 4;
      }
  printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], task, res, t);
  free(x);
  free(y);
  return 0;
  }
    
io_status solve2(double* x, double* y, double x0, int n, double* res)
  {
  int i, j;
  double el_n, el_prev, sum = 0;
  for (j = 0; j < n; j++)
      {
      for (i = n - 1; i > j; i--)
          {
          el_n = x[i];
          el_prev = x[i - j - 1];
          if (equal(el_n, el_prev)) return ERROR_FUNCTION;
          y[i] = (y[i] - y[i - 1]) / (el_n - el_prev);
          }
      }
  for (i = n - 1; i >= 0; i--)
      {
      sum = y[i] + (x0 - x[i]) * sum;
      }
  *res = sum;
  return SUCCESS;
  }
