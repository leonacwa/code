#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MOD = 1000000007;
int f[2][1005][1005];

int main()
{
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= 1000; ++i) {
		f[0][i][0] = 1;
		f[1][i][1] = 1;
	}
	for (int m = 2; m <= 1000; ++m) {
		for (int n = 1; n <= m; ++n) {
			f[0][m][n] = (f[0][m-1][n] + f[1][m-1][n]) % MOD;
			f[1][m][n] = (f[0][m][n-1] + f[1][m][n-1]) % MOD;
		}
	}
	int m, n;
	while (EOF != scanf("%d %d", &m, &n)) {
		printf("%d\n", (f[0][m][n]  + f[1][m][n]) % MOD);
	}
	return 0;
}

