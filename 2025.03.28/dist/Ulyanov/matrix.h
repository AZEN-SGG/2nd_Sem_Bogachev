#define EPS (1e-9)

void multmatvec(double*, double*, double*, int);
double scalp(double*, double*, int);
void vecdiff(double*, double*, int);
void vecmult(double*, double, int);
void veccpy(double*, double*, int);
void veccomb(double, double*, double, double*, int);
double count_task1(double*, double*, double, int);
double count_r1(double*, double*, double*, int);
double count_r2(double*, int);
int equal(double, double);
void multdiagvec(double*, double*, double*, int);
void deldiagvec(double*, double*, double*, int);
void deldiagmultvec(double*, double*, double*, double, int);
io_status checkdiag(double*, int);
void slaudown(double*, double*, double*, int);
void slauup(double*, double*, double*, int);
