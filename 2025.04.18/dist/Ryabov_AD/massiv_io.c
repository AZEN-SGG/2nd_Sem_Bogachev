#include <stdio.h>
#include <math.h>
#include "massiv_io.h"

int sravn_el(double x1, double x2){
    double eps = 1e-16;
    return fabs(x1 - x2) <= eps * fmax(fabs(x1), fabs(x2));
}

io_status read_file(double* x, double* y, int n, char* file_name){
    int i;
    FILE *fp;
    if (!(fp = fopen(file_name, "r"))){
        return ERROR_OPEN;
    }
    for (i = 0; i < n; i++){
        if (fscanf(fp, "%lf", x + i) != 1){
            fclose(fp);
            return ERROR_READ;
        }
        if (fscanf(fp, "%lf", y + i) != 1){
            fclose(fp);
            return ERROR_READ;
        }
    }
    fclose(fp);
    return SUCCESS;
}

io_status read_file_4(double* x, double* y, double*d, int n, char* file_name){
    int i, index;
    FILE *fp;
    if (!(fp = fopen(file_name, "r"))){
        return ERROR_OPEN;
    }
    index = 0;
    for (i = 0; i < n; i++){
        if (fscanf(fp, "%lf", x + i) != 1){
            fclose(fp);
            return ERROR_READ;
        }
        if (index < n){
            if (fscanf(fp, "%lf", y + index) != 1){
                fclose(fp);
                return ERROR_READ;
            }
        }
        else {
            if (fscanf(fp, "%lf", d + (index % n)) != 1){
                fclose(fp);
                return ERROR_READ;
            }
        }
        index++;
        if (index < n){
            if (fscanf(fp, "%lf", y + index) != 1){
                fclose(fp);
                return ERROR_READ;
            }
        }
        else {
            if (fscanf(fp, "%lf", d + (index % n)) != 1){
                fclose(fp);
                return ERROR_READ;
            }
        }
        index++;
    }
    fclose(fp);
    return SUCCESS;
}