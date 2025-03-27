#ifndef SOLVE_H
#define SOLVE_H

double t1_solve(const double * restrict A, double * restrict x_0, double * restrict x, int n, int m);
double t1_get_eigenvalue_approx(const double * restrict A, double * restrict x_k, double * restrict x, int n);
double t1_get_residual_norm(double * restrict x_k, double * restrict x, int n, double r1);
void t2_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, int n, int m, double t);
void t3_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m);
void t4_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m);
void t5_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m);
void t6_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m);
void t7_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m, double t);
void t8_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, double * restrict w, int n, int m, double t);

#endif
 
