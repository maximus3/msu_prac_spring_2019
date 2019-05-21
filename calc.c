#include <math.h>
#include <stdio.h>

int count;

double min(double a, double b)
{
	return a > b ? b : a;
}

double max(double a, double b)
{
	return a > b ? a : b;
}

int search_max(double *x, int n)
{
	int max_i = 0;
	for (int i = 1; i < n; i++)
	{
		if (x[i] > x[max_i])
			max_i = i;
	}
	return max_i;
}

int search_mid3(double x[])
{
	if (x[0] > x[1])
	{
		if (x[0] < x[2])
			return 0;
		else if (x[1] > x[2])
			return 1;
		else return 2;
	}
	else
	{
		if (x[1] < x[2])
			return 1;
		else if (x[0] > x[2])
			return 0;
		else return 2;
	}
}

double search_delta(double (*f)(double), double x1, double x2, double eps)
{
	double delta = 0;
	for(int i = 0; x1 + i * eps <= x2; i++)
	{
		delta = min(delta, f(x1 + i * eps));
	}
	return fabs(delta);
}

double integral(double (*f)(double), double a, double b, double eps, double delta)
{
	count = 0;
	if (b < a)
	{
		double c = a;
		a = b;
		b = c;
	}
	int n = 1;
	double h;
	double x;
	double intg_prev = 0, intg = 0;
	double s0 = f(a) + f(b) + 2 * delta;
	double sum = f(a) + f(b) + 2 * delta;
	
	while(1)
	{
		count++;
		intg = s0;
		h = (b - a) / n;
		x = a + h;
		while(x < b)
		{
			sum += 2 * f(x) + 2 * delta;
			x += 2 * h;
		}
		intg = sum * (h / 2);
		if(fabs(intg - intg_prev) < eps)
			return intg;
		intg_prev = intg;
		n *= 2;
	}
}

double root(double (*f)(double), double (*g)(double), double a, double b, double eps)
{
	count++;
	double x;
	double h_a = f(a) - g(a);
	double h_b = f(b) - g(b);
	
	while(1)
	{
		count++;
		x = a - h_a * (a - b) / (h_a - h_b);
		if(fabs(x - a) < eps) 
			return x;
		if ((f(a) - g(a)) * (f(x) - g(x)) < 0)
			b = x;
		else
			a = x;
		h_a = f(a) - g(a);
	}
}