// Program from 1Ex
#include "solve.h"

int t1_solve(char **a, int n, char *x, int (*cmp)(const char *, const char *)) {
	int avg = (n + (-1)*(n%2)) / 2;
	int comp;

	if (n == 0) return 0;
	
	comp = cmp(x, a[avg]);
	if (comp < 0) return t1_solve(a, avg, x, cmp);
	if (comp > 0) return avg+1 + t1_solve(a+avg+1, n-(avg+1), x, cmp);
	else return avg;
}

// Program from 2Ex

void t2_solve(char **arr_a, char **arr_b, char **arr_c, int n, int m, int (*cmp)(const char *, const char *))
{
 int i, j, k, cntr, len = n + m; // cntr - contrast
 for (i = 0, j = 0, k = 0; k < len; ++k)
 {
  if (i >= n) 
  {
   arr_c[k] = arr_b[j++];
  } else if (j >= m)
  {
   arr_c[k] = arr_a[i++];
  } else 
  {
   cntr = cmp(arr_a[i], arr_b[j]);
   if (cntr <= 0) arr_c[k] = arr_a[i++];
   else arr_c[k] = arr_b[j++];
  } 
 }
}

// Program from 3Ex

int t3_solve(char **a, int n, char *x, int (*cmp)(const char *, const char *)) {
    int i = 0, j = n-1;
    char *temp;

    while (1) 
    {
        for (; i < n; i++) if (cmp(a[i], x) >= 0) break;
        for (; j >= 0; j--) if (cmp(a[j], x) < 0) break;

        if (i >= j) break;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;

	i++, j--;
    }

    return i;
}

// Program from 4Ex

void t4_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	char *temp;
	int i, j;
	for (i=n; i > 0; --i)
	{
		for (j=0; j < i-1; ++j) 
		{
			if (cmp(a[j], a[j+1]) >= 0)
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;				
			}
		}
	}
}

// Program from 5Ex

void t5_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	char *temp;
	size_t size_c = sizeof(char);
	int i, min;
	for (i=0; i < n-1; ++i)
	{
		min = minimum(a+i*size_c, n-i, cmp)+i;
		temp = a[min];
		a[min] = a[i];
		a[i] = temp;
	}
}

int minimum(char **a, int n, int (*cmp)(const char *, const char *))
{
	int i, min=0;
	if (n <= 0) return 0;
	for (i = 1; i < n; ++i)
	{
		if (cmp(a[min], a[i]) > 0) min = i;
	}

	return min;
}

// Program from 6Ex

void t6_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	int i;
	for (i = 1; i < n; ++i)	t6_append(a, i+1, a[i], t6_find(a, i, a[i], cmp));
}

int t6_find(char **arr, int n, char *a, int (*cmp)(const char *, const char *))
{
	int i;
	for (i=0; i<n; ++i) if (cmp(a, arr[i]) < 0) break;
	return i;
}

void t6_append(char **arr, int n, char *a, int index)
{
	for (int i = n-1; i > index; --i) arr[i] = arr[i-1];
	arr[index] = a;
}

// Program from 7Ex

void t7_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	int i;
	for (i = 1; i < n; ++i)	t7_append(a, i+1, a[i], t7_find(a, i, a[i], cmp));
}

int t7_find(char **a, int n, char *x, int (*cmp)(const char *, const char *)) {
	int avg = (n + (-1)*(n%2)) / 2;
	int comp;

	if (n == 0) return 0;
	
	comp = cmp(x, a[avg]);
	if (comp < 0) return t7_find(a, avg, x, cmp);
	if (comp > 0) return avg+1 + t7_find(a+(avg+1), n-(avg+1), x, cmp);
	else return avg;
}

void t7_append(char **arr, int n, char *a, int index)
{
	for (int i = n-1; i > index; --i) arr[i] = arr[i-1];
	arr[index] = a;
}
// Program from 8Ex

void t8_solve(char **a, char **b, int n, int (*cmp)(const char *, const char *))
{
	int i = 2, j, margin;
	do {
		int hf_i = i/2;
		for (j = 0; j < n; j += i)
		{
			if (n < j+i)
			{
				margin = n-(j+hf_i);
				if (margin <= 0) break;
			} else margin = hf_i;

			unite(a+j, a+(j+hf_i), b, hf_i, margin, cmp);
			for (int k = 0; k < hf_i+margin; k++) a[j+k] = b[k];
		}

		i *= 2;
	} while (i < n*2);
}

void unite(char **arr_a, char **arr_b, char **arr_c, int n, int m, int (*cmp)(const char *, const char *))
{
 int i, j, k, cntr, len = n + m; // cntr - contrast
 for (i = 0, j = 0, k = 0; k < len; ++k)
 {
  if (i >= n) 
  {
   arr_c[k] = arr_b[j++];
  } else if (j >= m)
  {
   arr_c[k] = arr_a[i++];
  } else 
  {
   cntr = cmp(arr_a[i], arr_b[j]);
   if (cntr <= 0) arr_c[k] = arr_a[i++];
   else arr_c[k] = arr_b[j++];
  } 
 }
}

// Program from 9Ex

void t9_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	while (n > 1)
	{
		int is_edge = 0, ind_x = findIndex(a, n, a[n/2], cmp);
		if (ind_x < n-ind_x)
		{
			if (ind_x == 0) is_edge = 1;
			t9_solve(a, ind_x, cmp);
			a += ind_x + is_edge;
			n -= ind_x + is_edge;
		} else 
		{
			t9_solve(a+ind_x, n-ind_x, cmp);
			n = ind_x;
		}
	}
}

int findIndex(char **a, int n, char *x, int (*cmp)(const char *, const char *))
{	
    int i = 0, j = n-1;
    char *temp;

    while (1) 
    {
        for (; i < n; i++) if (cmp(a[i], x) >= 0) break;
        for (; j >= 0; j--) if (cmp(a[j], x) <= 0) break;

        if (i >= j) break;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;

	i++, j--;
    }

    return i;
}
