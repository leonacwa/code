#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

double A[101];
int n;

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%lf", &A[i]);
		}
		make_heap(A, A+n);
		while (n > 1) {
			double a = A[0];
			pop_heap(A, A+n);
			--n;
			double b = A[0];
			pop_heap(A, A+n);
			--n;
			a = 2 * sqrt(a * b);
			A[n] = a;
			++n;
			push_heap(A, A+n);
		}
		printf("%.3f\n", A[0]);
	}
	return 0;
}

