#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "massiv_io.h"
#include "solve.h"


int main(int argc, char*argv[]){
    double t, x0, eps;
    double res;
    if (!(argc == 3 && sscanf(argv[1], "%lf", &x0) == 1 && sscanf(argv[2], "%lf", &eps) == 1)){
        printf("Usage %s\n", argv[0]);
        return 1;
    }
    if (eps <= 0){
        printf("Negative precision and 0 not accepted");
        return 1;
    }
    t = clock();
    res = task05(x0, eps);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf ("%s : Task = %d Result = %e Residual = %e Elapsed = %.2f\n", argv[0], 5, res, fabs(res - sin(x0)), t);
    return 0;
}