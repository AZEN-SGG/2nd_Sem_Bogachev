#ifndef SOLVE_H
#define SOLVE_H

#define NUM_FPE 1e-300

#include "init_f.h"

#include <stddef.h>

static double (*f_global)(double) = NULL;

static inline double wf (double x)
{
		return f_global(x) * weight(x);
}

double t6_solve (
		double (*f) (double), 
		double a, double b,
		int n	
);

#endif
