#ifndef SOLVE_H
#define SOLVE_H

#include "status.h"

status t3_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x, int *m_it
		);

#endif
