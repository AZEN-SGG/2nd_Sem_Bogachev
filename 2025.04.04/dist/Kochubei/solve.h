#include "add.h"

void init_array(int* r, int n);

matrix_status gauss_step(restrict mat A, restrict mat B, int n, int k, int* r, double norm);

matrix_status gauss(restrict mat A, restrict mat B, restrict mat X, int n, int* r);

