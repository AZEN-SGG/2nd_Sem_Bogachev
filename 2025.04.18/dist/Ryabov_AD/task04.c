#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "massiv_io.h"
#include "solve.h"


int main(int argc, char*argv[]){
    double *x, *y, *d;
    int n, ret_f;
    double t, x0;
    double res;
    char *file_name;
    io_status ret;
    if (!(argc == 4 && sscanf(argv[1], "%lf", &x0) == 1 && sscanf(argv[2], "%d", &n) == 1)){
        printf("Usage %s\n", argv[0]);
        return 1;
    }
    if (n <= 0){
        printf("With zero points impossible to plot graph\n");
        return 1;
    }
    file_name = argv[3];
    // Массив x
    x = (double *)malloc(n * sizeof(double));
    if (!x){
        printf("No pamyat\n");
        return 2;
    }
    // Массив y
    y = (double *)malloc(n * sizeof(double));
    if (!y){
        printf("No pamyat\n");
        free(x);
        return 2;
    }
    d = (double *)malloc(n * sizeof(double));
    if (!d){
        printf("No pamyat\n");
        free(x);
        free(y);
        return 2;
    }
    ret = read_file_4(x, y, d, n, file_name);
    switch (ret){
        case SUCCESS:
            break;
        case ERROR_OPEN:
            printf("Can not open %s\n", file_name);
            break;
        case ERROR_READ:
            printf("Can not read %s\n", file_name);
            break;
        case ERROR_MEM:
            printf("Not enough memory\n");
            break;
        }
    if (ret != SUCCESS){
        free(x);
        free(y);
        free(d);
        return 3;
    }
    t = clock();
    ret_f = task04(x0, n, x, y, d, &res);
    if (ret_f){
        printf("Division by zero occurs. Most likely, were two identical points in file.");
        free(x);
        free(y);
        free(d);
        return 4;
    }
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], 4, res, t);
    free(x);
    free(y);
    free(d);
    return 0;
}