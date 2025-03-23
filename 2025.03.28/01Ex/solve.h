#ifndef SOLVE_H
#define SOLVE_H

double t1_solve(double * restrict A, double * restrict x_0, double * restrict x, int n, int m);
void matvec_mul(int n, double * restrict A, double * restrict x, double * restrict x_k);
double t1_get_eigenvalue_approx(double * restrict A, double * restrict x_k, double * restrict x, int n);
double t1_get_residual_norm(double * restrict x_k, double * restrict x, int n, double r1);

#endif
