#include <stdio.h>
double f(int n) 
{
	double s = 0;
	int i;
	for (i = 1; i <= n; ++i) {
		s += (i%2==1?1:-1)*1.0/i;
	}
	return s;
}

int main()
{
	int n, m;
	scanf("%d", &m);
	while (m--) {
		scanf("%d", &n);
		printf("%.2lf\n", f(n));
	}
	return 0;
}
