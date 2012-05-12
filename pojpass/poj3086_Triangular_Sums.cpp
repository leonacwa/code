#include <stdio.h>

long long T[305];

int main()
{
	int N;
	T[0] = 0;
	for (int i = 1; i <= 301; i++) {
		T[i] = T[i-1] + i;
	}
	scanf("%d", &N);
	for (int cs = 1; cs <= N; cs++) {
		int n;
		scanf("%d", &n);
		long long w = 0;
		for (int k = 1; k <= n; k++) {
			w += k * T[k+1];
		}
		printf("%d %d %lld\n", cs, n, w);
	}
	return 0;
}

