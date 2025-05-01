#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "io_status.h"
#include "functions.h"
#include "comparison.h"

int solve5(double, double, double, int, double*, double (*)(double));

int main(int argc, char* argv[])
  {
  int task = 5;
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
  it = solve5(a, b, eps, maxit, &x, f);
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
  
int solve5(double a, double b, double eps, int maxit, double* x, double (*f)(double))
  {
  int it;
  double c = (a + b) / 2, xi, fxi;
  double fa = (*f)(a), fb = (*f)(b), fc = (*f)(c);
  double der_ac, der_cb, der_acb;
  if (fabs(fa) < eps) {*x = a; return 0;}
  if (fabs(fb) < eps) {*x = b; return 0;}
  for (it = 0; it < maxit; it++)
      {
      if (!equal(fa, fc)) der_ac = (a - c) / (fa - fc);
      else return -1;
      if (!equal(fc, fb)) der_cb = (c - b) / (fc - fb);
      else return -1;
      if (!equal(fa, fb)) der_acb = (der_cb - der_ac) / (fb - fa);
      else return -1;
      xi = a - fa * der_ac + fa * fc * der_acb;
      fxi = (*f)(xi);
      if (fabs(fxi) < eps) {*x = xi; break;}
      if ((fabs(fa) >= fabs(fc)) && (fabs(fa) >= fabs(fb))) {a = xi; fa = fxi;}
      else if ((fabs(fc) >= fabs(fa)) && (fabs(fc) >= fabs(fb))) {c = xi; fc = fxi;}
      else {b = xi; fb = fxi;}
      }
  if (it >= maxit) return -1;
  return it;
  }
