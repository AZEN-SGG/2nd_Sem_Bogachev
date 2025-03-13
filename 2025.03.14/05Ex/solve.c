#include "solve.h"
#include "math.h"

#define eps 1e-9

int compare(const double a, const double b)
{
	if (a - b > eps) return 1;
	else if (b - a > eps) return -1;
	return 0;
}

double t5_solve(const double *A, const double *b, int n, int m)
{
	double temp, summa, maximum = 0;
	int i, j, k;

	if (n <= 0 || m <= 0) return 0;

	for (i = 0; i < n; i++)
	{
		summa = 0;
		for (k = 0; k < n; k++) {
			temp = 0;
			for (j = 0; j < m; j++)
				temp += A[i * m + j] * b[j * n + k];

			if (k == i) temp--;
			summa += fabs(temp);
		}
		if (compare(summa, maximum) == 1) maximum = summa;		
	}

	return maximum;
}

