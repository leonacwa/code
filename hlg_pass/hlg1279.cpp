#include <stdio.h>
int main()
{
	int n, m;
	while (EOF != scanf("%d %d", &n, &m)) {
		long long t = (long long)n*(n-1) + 2;
		if (t >=	m) {
			printf("%lld\n", t-m+1);
		} else {
			puts("N\\n");
		}
	}
	return 0;
}

