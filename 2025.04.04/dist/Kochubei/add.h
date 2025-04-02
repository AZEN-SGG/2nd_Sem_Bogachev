typedef enum io_status_ {
SUCCESS,
ERROR_OPEN,
ERROR_READ,
} io_status;

typedef enum matrix_status_ {
SOLVED,
FAILED,
} matrix_status;

typedef double* mat;

int max(int a, int b);

int min(int a, int b);

int abs(int a);

double f(int k, int n, int m, int i, int j);

io_status read_matrix(restrict mat A, int n, int m, char* name);

void print_matrix(restrict mat A, int n, int m, int p);

void init_matrix(restrict mat A, int n, int m, int k);

void init_vector(restrict mat A, restrict mat V, int n);

double vector_norm(restrict mat V, int n);

double R1(restrict mat A, restrict mat X, restrict mat B, int n);

double R2(restrict mat X, int n);

int equals_zero(double x, double norm);

double matrix_norm(restrict mat A, int n);

void divide_row(restrict mat A, int n, int k);

int find_max(restrict mat A, int n, int k);

void subtract_row(restrict mat A, int n, int a, int b);

void swap(double* a, double* b);

void swap_columns(restrict mat A, int n, int a, int b);

void swap_int(int* a, int* b);
