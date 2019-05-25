int count;

double f1(double);
double f2(double);
double f3(double);

double integral(double (*)(double), double, double, double, double);
double root(double (*)(double), double (*)(double), double, double, double);

double min(double, double);
double max(double, double);

double search_delta(double (*)(double), double, double, double);
int search_max(double (*), int);
int search_mid3(double (*));