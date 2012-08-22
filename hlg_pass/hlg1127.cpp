#include <stdio.h>
const int MOD = 1000000007;
int a[1005][1005];

int main()
{
	int n, m;
	for (int i = 0; i <= 1000; ++i) {
		a[i][0] = 1;
		a[0][i] = 1;
	}
	for (int i = 1; i <= 1000; ++i) {
		for (int j = 1; j <= 1000; ++j) {
			a[i][j] = (a[i][j-1] + a[i-1][j]) % MOD;
		}
	}
	while (EOF != scanf("%d %d", &n, &m)) {
		if (n == 0 && m == 0) break;
		printf("%d\n", a[n][m]);
	}
	return 0;
}

