/* hdu_vc_3726 B
 * 递推
 * */
#include <cstdio>
#include <cstring>

const int MOD = 100000007;
const int MAXN = 1005;

int f[MAXN][2][MAXN * 2];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	memset(f, 0, sizeof(f));
	while (nTest--) {
		int n, k;
		scanf("%d%d", &n, &k);
		f[1][0][1] = f[1][1][2] = 1;
		for (int i = 2; i <= n; ++i) {
			f[i][0][1] = (f[i-1][0][1] + f[i-1][0][0] + f[i-1][1][0] + f[i-1][1][1] + f[i-1][1][1]) % MOD;
			for (int j = 2; j <= k; ++j) {
				f[i][0][j] = f[i-1][0][j] + f[i-1][0][j-1] + f[i-1][1][j-1] + f[i-1][1][j] + f[i-1][1][j];
				if (f[i][0][j] >= MOD) f[i][0][j] %=  MOD;
				f[i][1][j] = f[i-1][0][j-1] + f[i-1][0][j-1] + f[i-1][0][j-2] + f[i-1][1][j-1] + f[i-1][1][j-2] + f[i-1][1][j-1] + f[i-1][1][j];
				if (f[i][1][j] >= MOD) f[i][1][j] %= MOD;
			}
		}
		printf("%d\n", (f[n][0][k] + f[n][1][k]) % MOD);
	}
	return 0;
}

