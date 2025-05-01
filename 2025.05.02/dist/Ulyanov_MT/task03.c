#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "io_status.h"
#include "functions.h"
#include "comparison.h"

int solve3(double, double, double, int, double*, double (*)(double));

int main(int argc, char* argv[])
  {
  int task = 3;
  double a, b, eps;
  int maxit, k;
  double t;
  double (*f)(double);
  double (*func[])(double) = {f0, f1, f2, f3, f4, f5, f6};
  double x = 0, fx;
  int it, c;
  if (!(argc == 6 && sscanf(argv[1], "%lf", &a) == 1 && sscanf(argv[2], "%lf", &b) == 1 && sscanf(argv[3], "%le", &eps) == 1 && sscanf(argv[4], "%d", &maxit) == 1 && sscanf(argv[5], "%d", &k) == 1 && k >= 0 && k <= 6))
      {
      printf("Usage: %s a b eps M k\n", argv[0]);
      return -2;
      }
  f = func[k];
  t = clock();
  it = solve3(a, b, eps, maxit, &x, f);
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
  
int solve3(double a, double b, double eps, int maxit, double* x, double (*f)(double))
  {
  int it;
  double c, fc;
  double fa = (*f)(a), fb = (*f)(b);
  if (fa * fb > 0) return -1;
  if (fabs(fa) < eps) {*x = a; return 0;}
  if (fabs(fb) < eps) {*x = b; return 0;}
  for (it = 0; it < maxit; it++)
      {
      if (!equal(fa, fb)) c = a - ((a - b) / (fa - fb)) * fa;
      else return -1;
      fc = (*f)(c);
      if (fabs(fc) < eps) {*x = c; break;}
      if (fc * fa > 0) {a = c; fa = fc;}
      if (fc * fb > 0) {b = c; fb = fc;}
      }
  if (it >= maxit) return -1;
  return it;
  }
