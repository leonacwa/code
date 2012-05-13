#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MOD = 2011;
int score[63];
int f[63][1001+1];

int main()
{
	int c = 0, n = 1001;
	for (int i = 1; i <= 20; ++i) score[c++] = i;
	score[c++] = 25;
	for (int i = 1; i <= 20; ++i) score[c++] = 3 * i;
	for (int i = 1; i <= 20; ++i) score[c++] = 2 * i;
	score[c++] = 50;

	for (int i = 0; i <= n; ++i) f[0][i] = 1;
	for (int i = 1; i < c; ++i) {
		for (int j = 0; j <= n; ++j) {
			f[i][j] = 0;
			for (int k = 0; k <= j; k += score[i]) {
				f[i][j] += f[i-1][j - k];
				f[i][j] %= MOD;
			}
		}
	}

	while (EOF != scanf("%d", &n) && n > 0) {
		printf("%d\n", (f[61][n] - f[40][n] + MOD) % MOD);
	}
	return 0;
}

