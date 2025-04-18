#ifndef SOLVE_H
#define SOLVE_H

double t1_solve (const double x_0, const int n, const double * restrict X, const double * restrict Y);
double t2_solve (const double x_0, const int n, const double * restrict X, double * restrict Y);
double t3_solve (const double x_0, const int n, const double * restrict X, double * restrict Y);
double t4_solve (
		const double x_0, const int n, 
		const double * restrict X, 
		double * restrict Y,
		double * restrict D
		);
double fsin (double x, const double eps);
double fcos (double x, const double eps);
double fexp (double x, const double eps);
double dln (double x, const double eps);

#endif
