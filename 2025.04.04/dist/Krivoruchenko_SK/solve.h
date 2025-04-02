#ifndef SOLVE_H
#define SOLVE_H

int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c);
void gauss_inverse(const int n, const int k, double * restrict A, double * restrict X);
void gauss_back_substitution(const int n, double * restrict A, double * restrict X);

#endif
