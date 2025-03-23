#ifndef SOLVE_H
#define SOLVE_H

int compare(const double a, const double b);
double t1_solve(double *a, int m, int n);
void matvec_mul(int n, double * restrict A, double * restrict x, double * restrict x_k);

#endif
