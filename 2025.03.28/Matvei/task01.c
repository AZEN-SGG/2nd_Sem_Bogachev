#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "matrix.h"

double solve1(double*, double*, double*, int, int);

int main(int argc, char* argv[])
    {
    int task = 1;
    double* a;
    double* x0;
    double* x;
    int n, m, p, k1, k2;
    char* name1 = 0;
    char* name2 = 0;
    double r1, r2;
    double t;
     if (!((argc == 6 || argc == 7 || argc == 8) && sscanf(argv[1], "%d", &m) == 1 && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &k1) == 1 && k1 >= 0 && k1 <= 4))
        {
        printf("Usage: %s n m p k1 [file1] k2 [file2]\n", argv[0]);
        return 1;
        }
    if (k1 == 0)
        {
        if (!(sscanf(argv[6], "%d", &k2) == 1) && k2 >= 0 && k2 <= 4)
            {
            printf("Usage: %s n m p k1 [file1] k2 [file2]\n", argv[0]);
            return 1;
            }
        name1 = argv[5];
        }
    else
        {
        if (!(sscanf(argv[5], "%d", &k2) == 1) && k2 >= 0 && k2 <= 4)
            {
            printf("Usage: %s n m p k1 [file1] k2 [file2]\n", argv[0]);
            return 1;
            }
        }
    if (k2 == 0)
        {
        if (k1 == 0) name2 = argv[7];
        else name2 = argv[6];
        }
    a = (double*) malloc(n * n * sizeof(double));
    if (!a)
        {
        printf("Not enough memory\n");
        return 2;
        }
    if (name1)
        {
        io_status ret;
        ret = read_matrix(a, n, n, name1);
        do
            {
            switch(ret)
                {
                case SUCCESS:
                    continue;
                case ERROR_OPEN:
                    printf("Can not open file %s\n", name1);
                    break;
                case ERROR_READ:
                    printf("Can not read file %s\n", name1);
                    break;
                }
            free(a);
            return 3;
            } while (0); 
        }
    else
        init_matrix(a, n, n, k1);
    x0 = (double*) malloc(n * sizeof(double));
    if (!x0)
        {
        printf("Not enough memory\n");
        free(a);
        return 2;
        }
    x = (double*) malloc(n * sizeof(double));
    if (!x)
        {
        printf("Not enough memory\n");
        free(a);
        free(x0);
        return 2;
        }
    if (name2)
        {
        io_status ret;
        ret = read_matrix(x0, n, 1, name2);
        do
            {
            switch(ret)
                {
                case SUCCESS:
                    continue;
                case ERROR_OPEN:
                    printf("Can not open file %s\n", name2);
                    break;
                case ERROR_READ:
                    printf("Can not read file %s\n", name2);
                    break;
                }
            free(a);
            free(x0);
            free(x);
            return 3;
            } while (0); 
        }
    else
        init_matrix(x0, n, 1, k2);
    printf("Matrix:\n");
    print_matrix(a, n, n, p);
    printf("Vector:\n");
    print_matrix(x0, n, 1, p);
    t = clock();
    r1 = solve1(a, x0, x, n, m);
    t = (clock() - t) / CLOCKS_PER_SEC;
    r2 = count_task1(a, x, r1, n);
   
   printf("Vector x:\n"); 
    if (m % 2)
    	print_matrix(x, 1, n, p);
    else
	   print_matrix(x0, 1, n, p); 
    printf ("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f\n", argv[0], task, r1, r2, t);
    free(a);
    free(x0);
    free(x);
    return 0;
    }
    
double solve1(double* a, double* x0, double* x, int n, int m)
  {
  int k;
  double lambda;
  if (m <= 0) return 0;
  for (k = 0; k <= m; k++)
      {
      if (k % 2) multmatvec(a, x, x0, n);
      else multmatvec(a, x0, x, n);
      }
  if (m % 2) lambda = scalp(x0, x, n) / scalp(x, x, n);
  else lambda = scalp(x, x0, n) / scalp(x0, x0, n);
  return lambda;
  }
