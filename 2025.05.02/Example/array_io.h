#ifndef ARRAY_IO_H
#define ARRAY_IO_H

#include "io_status.h"

io_status read_values_and_derivatives (
		double * restrict X, 
		double * restrict Y, 
		double * restrict D, 
		const int n, 
		const char * restrict name
		);
void print_values_and_derivatives (
		const double * restrict X, 
		const double * restrict Y, 
		const double * restrict D, 
		const int n, const int p
		);

#endif
