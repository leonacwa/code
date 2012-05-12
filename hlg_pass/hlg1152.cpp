// hlg 1152
#include <stdio.h>
#include <math.h>

int mi(int a, int b, int m) {
	int t;
	if (b == 0)
		return 1%m;
	if (b == 1) 
		return a%m;
	t = mi(a, b/2, m);
	t = t*t%m;
	if (b%2 == 1)
		t = t*a%m;
	return t%m;
}

int main()
{
	int a, b, m, t;
	while (EOF != scanf("%d %d %d", &a, &b, &m)) {
		if (a == 1 || b == 1) {
			printf("%d\n", (a+b)%m);
			continue;
		}
		if (log(1.0*b)/log(1.0*a)+1e-6 < 1.0*b/a) {
			printf("%d\n", mi(a%m, b, m));
		}
		else {
			printf("%d\n", mi(b%m, a, m));
		}
	}
	return 0;
}
