#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "comparison.h"

int solve3(double*, int, int);

int main(int argc, char* argv[])
    {
    int task = 3;
    double* a;
    int n, m, p, k;
    char* name = 0;
    int res;
    double t;
    if (!((argc == 5 || argc == 6) && sscanf(argv[1], "%d", &m) == 1 && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p) == 1 && sscanf(argv[4], "%d", &k) == 1 && k >= 0 && k <= 4))
        {
        printf("Usage: %s m n p k [name]\n", argv[0]);
        return 1;
        }
    if (k == 0)
        name = argv[5];
    a = (double*) malloc(m * n * sizeof(double));
    if (!a)
        {
        printf("Not enough memory\n");
        return 2;
        }
    if (name)
        {
        io_status ret;
        ret = read_matrix(a, m, n, name);
        do
            {
            switch(ret)
                {
                case SUCCESS:
                    continue;
                case ERROR_OPEN:
                    printf("Can not open file %s\n", name);
                    break;
                case ERROR_READ:
                    printf("Can not read file %s\n", name);
                    break;
                }
            free(a);
            return 3;
            } while (0); 
        }
    else
        init_matrix(a, m, n, k);
    printf("Matrix:\n");
    print_matrix(a, m, n, p);
    t = clock();
    res = solve3(a, m, n);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("New matrix:\n");
    print_matrix(a, m, n - 1, p);
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
    free(a);
    return 0;
    }
    
int solve3(double* a, int m, int n)
  {
  int i, j, ind_min_j = 0;
  double min, sum = 0;
  int l = 0;
  if ((m == 0) && (n == 0)) return 0;
  for (i = 0; i < m; i++) sum += fabs(a[i * n + 0]);
  min = sum;
  for (j = 1; j < n; j++)
      {
      sum = 0;
      for (i = 0; i < m; i++) sum += fabs(a[i * n + j]);
      if (sum < min)
          {
          min = sum;
          ind_min_j = j;
          }
      }
  for (i = 0; i < m; i++)
      {
      for (j = 0; j < n; j++)
          {
          if (j != ind_min_j)
              {
              a[l] = a[i * n + j];
              l++;
              }
          }
      }
  return ind_min_j + 1;
  }
