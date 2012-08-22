// hlg 1151
#include <stdio.h>
#define MAXN 1004
int f[MAXN+1][MAXN+1];
int opt[MAXN+1];
int main()
{
	int Case = 0, k, q, t, i, j;
	while (scanf("%d%d%d", &k, &q, &t) != EOF) {
		for (i = 1; i <= MAXN; ++i) {
			f[0][i] = k % i;
			f[1][i] = q % i;
		}
		for (i = 2; i <= MAXN; ++i) {
			for (j = 1; j <= MAXN; ++j) {
				f[i][j] = (f[i-1][j] + f[i-2][j]) % j;
			}
		}
		for (i = 0; i <= MAXN; ++i) {
			int cnt = 0;
			for (j = 1; j <= i; ++j) {
				if (f[i][j] == 0) 
					cnt++;
			}
			opt[i] = cnt;
		}
		printf("Case %d:\n", ++Case);
		while (t--) {
			scanf("%d", &j);
			printf("%d\n", opt[j]);
		}
	}
	return 0;
}

