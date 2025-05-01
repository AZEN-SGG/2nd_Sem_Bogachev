#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "io_status.h"
#include "functions.h"
#include "comparison.h"

int solve8(double, double, double, int, double*, double (*)(double));

int main(int argc, char* argv[])
  {
  int task = 8;
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
  it = solve8(a, b, eps, maxit, &x, f);
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
  
int solve8(double a, double b, double eps, int maxit, double* x, double (*f)(double))
  {
  int it;
  double h = 0.1;
  double xi = a, fxi = (*f)(a), fx;
  for (it = 0; it < maxit; it++)
      {
      xi += (b - a) * h;
      fx = (*f)(xi);
      if (fx < fxi) h *= -0.1;
      else if (equal(xi, a)) {*x = xi; break;}
      else if (equal(xi, b)) {*x = xi; break;}
      if (fabs(h) < eps) {*x = xi; break;}
      fxi = fx;
      }
  if (it >= maxit) return -1;
  return it;
  }
