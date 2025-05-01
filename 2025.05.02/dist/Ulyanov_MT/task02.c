#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "io_status.h"
#include "functions.h"
#include "comparison.h"

int solve2(double, double, int, double*, double (*)(double), double (*)(double));

int main(int argc, char* argv[])
  {
  int task = 2;
  double x0, eps;
  int maxit, k;
  double t;
  double (*f)(double);
  double (*der_f)(double);
  double (*func[])(double) = {f0, f1, f2, f3, f4, f5, f6};
  double (*der_func[])(double) = {der_f0, der_f1, der_f2, der_f3, der_f4, der_f5, der_f6};
  double x = 0, fx;
  int it, c;
  if (!(argc == 5 && sscanf(argv[1], "%lf", &x0) == 1 && sscanf(argv[2], "%le", &eps) == 1 && sscanf(argv[3], "%d", &maxit) == 1 && sscanf(argv[4], "%d", &k) == 1 && k >= 0 && k <= 6))
      {
      printf("Usage: %s x0 eps M k\n", argv[0]);
      return -1;
      }
  f = func[k];
  der_f = der_func[k];
  t = clock();
  it = solve2(x0, eps, maxit, &x, f, der_f);
  t = (clock() - t) / CLOCKS_PER_SEC;
  c = get_count();
  if (it < 0)
      {
      printf("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, c, t);
      return -1;
      }
  fx = (*f)(x);
  printf("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, fx, it, c, t);
  return 0;
  }
  
int solve2(double x0, double eps, int maxit, double* x, double (*f)(double), double (*der_f)(double))
  {
  int it;
  double fx;
  double der;
  for (it = 0; it < maxit; it++)
      {
      fx = (*f)(x0);
      if (fabs(fx) < eps) break;
      der = der_f(x0);
      if (!(equal(der, 0))) x0 = x0 - fx / der;
      else return -1;
      }
  if (it >= maxit) return -1;
  *x = x0;
  return it;
  }
