#ifndef MATRIX_H
#define MATRIX_H

void init_vec_b(const double * restrict a, double * restrict b, int n);
void matvec_mul(int n, const double * restrict A, const double * restrict x, double * restrict x_k);
double get_r1(const double * restrict A, const double * restrict x_k, const double * restrict b, int n);
double get_r2_value(const double * restrict x_k, int n);

#endif
