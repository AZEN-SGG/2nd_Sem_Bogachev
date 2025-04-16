#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "functions.h"

double solve7(double, double);

int main(int argc, char* argv[])
  {
  int task = 7;
  double x, eps;
  double res;
  double diff;
  double t;
  if (!((argc == 3) && sscanf(argv[1], "%le", &x) == 1 && sscanf(argv[2], "%le", &eps) == 1))
      {
      printf("Usage: %s x0 eps\n", argv[0]);
      return 1;
      }
  t = clock();
  res = solve7(x, eps);
  t = (clock() - t) / CLOCKS_PER_SEC;
  diff = fabs(res - exp(x));
  printf ("%s : Task = %d Result = %e Residual = %e Elapsed = %.2f\n", argv[0], task, res, diff, t);
  return 0;
  }
  
double solve7(double x, double eps)
  {
  int i = 1, intg;
  double mult = 1, el = 1, res = 0;
  intg = floor(x);
  x = x - intg;
  while (fabs(el) >= eps)
      {
      res += el;
      el *= x / i;
      i++;
      }
  for (i = 0; i < intg; i++)
      {
      mult *= M_E;
      }
  return mult * res;
  }
