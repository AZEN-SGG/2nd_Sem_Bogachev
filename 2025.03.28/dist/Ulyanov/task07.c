#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "matrix.h"

void solve7(double*, double*, double*, double*, int, int, double);

int main(int argc, char* argv[])
    {
    int task = 7;
    double* a;
    double* x0;
    double* x;
    double* b;
    int n, m, p, k1, k2;
    char* name1 = 0;
    char* name2 = 0;
    double tau;
    double r1, r2;
    double t;
     if (!((argc == 7 || argc == 8 || argc == 9) && sscanf(argv[1], "%lf", &tau) == 1 && sscanf(argv[2], "%d", &m) == 1 && sscanf(argv[3], "%d", &n) == 1 && sscanf(argv[4], "%d", &p) == 1 && sscanf(argv[5], "%d", &k1) == 1 && k1 >= 0 && k1 <= 4))
        {
        printf("Usage: %s tau n m p k1 [file1] k2 [file2]\n", argv[0]);
        return 1;
        }
    if (k1 == 0)
        {
        if (!(sscanf(argv[7], "%d", &k2) == 1) && k2 >= 0 && k2 <= 4)
            {
            printf("Usage: %s tau n m p k1 [file1] k2 [file2]\n", argv[0]);
            return 1;
            }
        name1 = argv[6];
        }
    else
        {
        if (!(sscanf(argv[6], "%d", &k2) == 1) && k2 >= 0 && k2 <= 4)
            {
            printf("Usage: %s tau n m p k1 [file1] k2 [file2]\n", argv[0]);
            return 1;
            }
        }
    if (k2 == 0)
        {
        if (k1 == 0) name2 = argv[8];
        else name2 = argv[7];
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
    b = (double*) malloc(n * sizeof(double));
    if (!b)
        {
        printf("Not enough memory\n");
        free(a);
        free(x0);
        free(x);
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
            free(b);
            return 3;
            } while (0); 
        }
    else
        init_matrix(x0, n, 1, k2);
    init_vector(b, a, n);
    if (checkdiag(a, n) == ERROR_READ)
        {
        printf("Inverse matrix does not exist\n");
        free(a);
        free(x0);
        free(x);
        free(b);
        return 4;
        }
    printf("Matrix:\n");
    print_matrix(a, n, n, p);
    printf("Vector:\n");
    print_matrix(x0, n, 1, p);
    printf("Vector b:\n");
    print_matrix(b, n, 1, p);
    t = clock();
    solve7(a, x0, x, b, n, m, tau);
    t = (clock() - t) / CLOCKS_PER_SEC;
    r1 = count_r1(a, b, x, n);
    r2 = count_r2(x, n);
    printf("New vector:\n");
    print_matrix(x, n, 1, p);
    printf ("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f\n", argv[0], task, r1, r2, t);
    free(a);
    free(x0);
    free(x);
    free(b);
    return 0;
    }
    
void solve7(double* a, double* x0, double* x, double* b, int n, int m, double tau)
  {
  int k;
  veccpy(x, x0, n);
  for (k = 1; k <= m; k++)
      {
      multmatvec(a, x, x0, n);
      vecdiff(x0, b, n);
      deldiagmultvec(a, x0, x0, tau, n);
      vecdiff(x, x0, n);
      }
  }
