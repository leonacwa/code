#include <stdio.h>
#include <string.h>
#include <math.h>

void adjust_heap(double A[], int pr, int n) // down adjust
{
	double *ptr = A - 1;
	double t;
	int c = pr;
	while (c*2 <= n) {
		c *= 2;
		if (c < n && ptr[c] < ptr[c+1]) ++c;
		if (ptr[c / 2] < ptr[c]) {
			t = ptr[c / 2];
			ptr[c / 2] = ptr[c];
			ptr[c] = t;
		} else {
			break;
		}
	}
}

void make_heap(double A[], int n)
{
	double *ptr = A - 1;
	for (int i = n / 2; i > 0; --i) {
		adjust_heap(A, i, n);
	}
}

void pop_heap(double A[], int n)
{
	double *ptr = A - 1;
	double t;
	t = ptr[1];
	ptr[1] = ptr[n];
	ptr[n] = t;
	adjust_heap(A, 1, n-1);
}

void push_heap(double A[], int n)
{
	double *ptr = A -1;
	double t = ptr[n];
	int c = n;
	while (c > 1 && ptr[c / 2] < t) {
		ptr[c] = ptr[c / 2];
		c /= 2;
	}
	ptr[c] = t;
}

double A[101];
int n;

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%lf", &A[i]);
		}
		make_heap(A, n);
		while (n > 1) {
			double a = A[0];
			pop_heap(A, n);
			--n;
			double b = A[0];
			pop_heap(A, n);
			--n;
			a = 2 * sqrt(a * b);
			A[n] = a;
			++n;
			push_heap(A, n);
		}
		printf("%.3f\n", A[0]);
	}
	return 0;
}

