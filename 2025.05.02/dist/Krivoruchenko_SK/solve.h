#ifndef SOLVE_H
#define SOLVE_H

int t1_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
		);

int t2_solve (
		double (*f) (double), 
		double (*d) (double), 
		double x_0, double eps, 
		int m, double *x
		);

int t3_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
		);
		
int t4_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
		);
		
int t7_solve (
		double (*f) (double), 
		double x_0, double eps, 
		int m, double *x
		);
	
int t8_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
		);

#endif
