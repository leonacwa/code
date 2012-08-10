#include <stdio.h>
#include <string.h>

long long f[32][32];
int n;

int main()
{
	while (EOF != scanf("%d", &n) && n != 0) {
		f[0][0] = 0;
		f[1][0] = 1;
		for (int i = 1; i <= n; ++i) f[0][i] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= n; ++j) {
				f[i][j] = f[i-1][j+1];
				if (j > 0) {
					f[i][j] += f[i][j-1];
				}
			}
		}
		printf("%I64d\n", f[n][0]);
	}
	return 0;
}

