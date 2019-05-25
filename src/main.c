#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lib.h"

int s_in_a(char *s, char *arr[], int n)
{
	for(int i = 0; i < n; i++)
		if (strcmp(arr[i], s) == 0) return i;
	return 0;
}

double test_f1(double x)
{
	return 2 / x;
}

double test_f2(double x)
{
	return x;
}

double test_f3(double x)
{
	return x * x;
}

int main(int argc, char *argv[])
{
	double eps_d = 1e-3;
	double eps = 1e-3;
	double eps1 = 1e-3, eps2 = 1e-3;
	int k;
	if (s_in_a("-help", argv, argc))
	{
		printf("Square\nUsage:  square.e [option] ...\n");
		printf("Options:\n\t-help\n\t-Scount - show count of iterations\n\t-Ssolution - show solutions\n\t-Sintegral - show integrals\n\t-Sdelta - show delta\n\t-root\n\t-integral\n");
		return 0;
	}
	k = s_in_a("-integral", argv, argc);
	if (k)
	{
		printf("F1: 2/x\nF2: x\nF3: x^2\n\n");
		printf("Integral F1: %.3lf\n", integral(test_f1, atoi(argv[k + 1]), atoi(argv[k + 2]), eps2, 0));
		printf("Integral F2: %.3lf\n", integral(test_f2, atoi(argv[k + 1]), atoi(argv[k + 2]), eps2, 0));
		printf("Integral F3: %.3lf\n", integral(test_f3, atoi(argv[k + 1]), atoi(argv[k + 2]), eps2, 0));
		return 0;
	}
	if (s_in_a("-root", argv, argc))
	{
		printf("F1: 2/x\nF2: x\nF3: x^2\n\n");
		printf("Root F1 VS F2: %.3lf\n", root(test_f1, test_f2, 0.5, 5, eps1));
		printf("Root F1 VS F3: %.3lf\n", root(test_f1, test_f3, 0.5, 5, eps1));
		printf("Root F2 VS F3: %.3lf\n", root(test_f2, test_f3, 0.5, 5, eps1));
		return 0;
	}
	double a12 = 0.5, b12 = 7;
	double a13 = 0.5, b13 = 7;
	double a23 = 0.5, b23 = 7;
	double x[3]; // 1_2, 1_3, 2_3
	double y[3]; // 1_2, 1_3, 2_3
	double s[3]; // 1_2, 1_3, 2_3
	int iter_root[3];
	int iter_intg[3];
	double square;
	
	x[0] = root(f1, f2, a12, b12, eps1);
	iter_root[0] = count;
	x[1] = root(f1, f3, a13, b13, eps1);
	iter_root[1] = count;
	x[2] = root(f2, f3, a23, b23, eps1);
	iter_root[2] = count;
	y[0] = f1(x[0]);
	y[1] = f1(x[1]);
	y[2] = f2(x[2]);
	
	int bcount = s_in_a("-Scount", argv, argc);
	int bsol = s_in_a("-Ssolution", argv, argc);
	int bintg = s_in_a("-Sintegral", argv, argc);
	
	if (bsol) printf("f1 VS f2: %.3lf %.3lf\n", x[0], y[0]);
	if (bcount) printf("Iterations f1 VS f2: %d\n", iter_root[0]);
	if (bsol) printf("f1 vs f3: %.3lf %.3lf\n", x[1], y[1]);
	if (bcount) printf("Iterations f1 VS f3: %d\n", iter_root[1]);
	if (bsol) printf("f2 VS f3: %.3lf %.3lf\n", x[2], y[2]);
	if (bcount) printf("Iterations f2 VS f3: %d\n", iter_root[2]);
	
	double delta = search_delta(f1, min(x[0], x[1]), max(x[0], x[1]), eps_d);
	delta = max(delta, search_delta(f2, min(x[0], x[2]), max(x[0], x[2]), eps_d));
	delta = max(delta, search_delta(f3, min(x[1], x[2]), max(x[1], x[2]), eps_d));
	delta += 2;
	if (s_in_a("-Sdelta", argv, argc)) printf("Delta = %.3lf\n", delta);
	
	s[0] = integral(f1, x[0], x[1], eps2, delta);
	s[1] = integral(f2, x[0], x[2], eps2, delta);
	s[2] = integral(f3, x[1], x[2], eps2, delta);
	
	if (bintg) printf("S1 (from %.3lf to %.3lf): %.3lf\n", min(x[0], x[1]), max(x[0], x[1]), s[0]);
	if (bcount) printf("Iterations S1: %d\n", iter_intg[0]);
	if (bintg) printf("S2 (from %.3lf to %.3lf): %.3lf\n", min(x[0], x[2]), max(x[0], x[2]), s[1]);
	if (bcount) printf("Iterations S2: %d\n", iter_intg[1]);
	if (bintg) printf("S3 (from %.3lf to %.3lf): %.3lf\n", min(x[1], x[2]), max(x[1], x[2]), s[2]);
	if (bcount) printf("Iterations S3: %d\n", iter_intg[2]);
	
	int max_i = search_max(y, 3);
	int mid_i = search_mid3(x);
	if (max_i == mid_i)
	{
		switch (max_i)
		{
			case 0:
				printf("0\n");
				square = s[0] + s[1] - s[2];
				break;
			case 1:
				printf("1\n");
				square = s[0] + s[2] - s[1];
				break;
			case 2:
				printf("2\n");
				square = s[1] + s[2] - s[0];
				break;
			default:
				break;
		}
	}
	else
	{
		switch (mid_i)
		{
			case 0:
				square = s[2] - s[0] - s[1];
				break;
			case 1:
				square = s[1] - s[0] - s[2];
				break;
			case 2:
				square = s[0] - s[1] - s[2];
				break;
			default:
				break;
		}
	}
	
	printf("Square = %.3lf\n", square);
}
