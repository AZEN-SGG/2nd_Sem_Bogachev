#ifndef SOLVE_H
#define SOLVE_H

void t2_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, int n, int m, double t);
double t2_get_r1(const double * restrict A, const double * restrict x_k, const double * restrict b, int n);
double t2_get_r2_value(const double * restrict x_k, int n);

#endif
