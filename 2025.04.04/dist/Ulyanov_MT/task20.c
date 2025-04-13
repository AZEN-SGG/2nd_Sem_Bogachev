#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "matrix.h"

io_status inverse(double*, double*, int*, int);

int main(int argc, char* argv[])
    {
    io_status res;
    int task = 20;
    double* a;
    double* b;
    int* ind;
    int n, p, k;
    char* name = 0;
    double r1, r2;
    double t;
     if (!((argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &p) == 1 && sscanf(argv[3], "%d", &k) == 1 && k >= 0 && k <= 4))
        {
        printf("Usage: %s n p k [file]\n", argv[0]);
        return 1;
        }
    if (k == 0) name = argv[4];
    a = (double*) malloc(n * n * sizeof(double));
    if (!a)
        {
        printf("Not enough memory\n");
        return 2;
        }
    if (name)
        {
        io_status ret;
        ret = read_matrix(a, n, n, name);
        if (ret != SUCCESS)
            {
            switch(ret)
                {
                case ERROR_OPEN:
                    printf("Can not open file %s\n", name);
                    break;
                case ERROR_READ:
                    printf("Can not read file %s\n", name);
                    break;
                default:
                    printf("Unknown error %d in file %s\n", ret, name);
                }
            free(a);
            return 3;
            }
        }
    else
        init_matrix(a, n, n, k);
    b = (double*) malloc(n * n * sizeof(double));
    if (!b)
        {
        printf("Not enough memory\n");
        free(a);
        return 2;
        }
    init_idmatrix(b, n);
    ind = (int*) malloc(n * sizeof(int));
    if (!ind)
        {
        printf("Not enough memory\n");
        free(a);
        free(b);
        return 2;
        }
    init_ind(ind, n);
    printf("Matrix:\n");
    print_matrix(a, n, n, p);
    t = clock();
    res = inverse(a, b, ind, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    if (res == ERROR_MATRIX)
        {
        printf("Method is not applicable or inverse matrix does not exist\n");
        free(a);
        free(b);
        free(ind);
        return 0;
        }
    if (name) read_matrix(a, n, n, name);
    else init_matrix(a, n, n, k);
    r1 = count_r1(a, b, n);
    r2 = count_r2(a, b, n);
    printf("Inverse matrix:\n");
    print_matrix(b, n, n, p);
    printf ("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f K = %d N = %d\n", argv[0], task, r1, r2, t, k, n);
    free(a);
    free(b);
    free(ind);
    return 0;
    }
    
io_status inverse(double* a, double* b, int* ind, int n)
  {
  int tmp, i, j, k, ind_max_i, ind_max_j;
  double bag, mod_el_a, el_aik, el_akk, max, norm;
  norm = count_norm(a, n);
  for (k = 0; k < n; k++)
      {
      max = 0;
      ind_max_i = k;
      ind_max_j = k;
      for (i = k; i < n; i++)
          {
          for (j = k; j < n; j++)
              {
              mod_el_a = fabs(a[i * n + j]);
              if (mod_el_a > max)
                  {
                  max = mod_el_a;
                  ind_max_i = i;
                  ind_max_j = j;
                  }
              }
          }
      for (j = k; j < n; j++)
          {
          bag = a[k * n + j];
          a[k * n + j] = a[ind_max_i * n + j];
          a[ind_max_i * n + j] = bag;
          }
      for (j = 0; j < n; j++)
          {
          bag = b[k * n + j];
          b[k * n + j] = b[ind_max_i * n + j];
          b[ind_max_i * n + j] = bag;
          }
      for (i = 0; i < n; i++)
          {
          bag = a[i * n + k];
          a[i * n + k] = a[i * n + ind_max_j];
          a[i * n + ind_max_j] = bag;
          }    
      tmp = ind[k];
      ind[k] = ind[ind_max_j];
      ind[ind_max_j] = tmp;
      el_akk = a[k * n + k];
      if (is_null(el_akk, norm)) return ERROR_MATRIX;
      for (j = k + 1; j < n; j++) a[k * n + j] = a[k * n + j] / el_akk;
      for (j = 0; j < n; j++) b[k * n + j] = b[k * n + j] / el_akk;
      for (i = 0; i < n; i++)
          {
          if (i != k)
              {
              el_aik = a[i * n + k];
              for (j = k + 1; j < n; j++) a[i * n + j] = a[i * n + j] - el_aik * a[k * n + j];
              for (j = 0; j < n; j++) b[i * n + j] = b[i * n + j] - el_aik * b[k * n + j];
              }
          }
      }
      tmp = -1;
      for (i = 0; i < n; i++)
          {
          while (i != tmp)
              {
              tmp = ind[i];
              for (j = 0; j < n; j++)
                  {
                  bag = b[tmp * n + j];
                  b[tmp * n + j] = b[i * n + j];
                  b[i * n + j] = bag;
                  }
              ind[i] = ind[tmp];
              ind[tmp] = tmp;
              }
          }

  return SUCCESS;
  }
