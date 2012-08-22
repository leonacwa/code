#include <stdio.h>

long long C(int m, int n)
{
	long long s = 1, b = 1;
	for (int i = 1; i <= m; i++) {
		s *= (n-i+1);
		/**/
		if (s % b == 0) {
			s /= b;
			b = 1;
		}
		if (s % i == 0) {
			s /= i;
		} else {
			b *= i;
		}
		/**/
	}
//	printf("C:%lld %lld\n", s, b);
	return s / b;
}
long long f[28];
int main()
{
	int nCase, n, m;
	f[0] = 0;
	f[1] = 0;
	f[2] = 1;
	for (int i = 3; i <= 20; i++) {
		f[i] = (i-1)*(f[i-1] + f[i-2]);
	}
	scanf("%d", &nCase);
	while (nCase--) {
		scanf("%d %d", &n, &m);
		long long ans = C(m, n) * f[m];
		printf("%lld\n", ans);
	}
	return 0;
}

