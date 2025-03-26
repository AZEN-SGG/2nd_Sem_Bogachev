#ifndef SOLVE_H
#define SOLVE_H

void t3_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m);
double get_r1(const double * restrict A, const double * restrict x_k, const double * restrict b, int n);
double get_r2_value(const double * restrict x_k, int n);

#endif
