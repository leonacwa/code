#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MOD = 1000000007;
int x, y, a, b;
int f[101][101][2];

int dp(int x, int y, int s)
{
	if (f[x][y][s] != -1) return f[x][y][s];
	f[x][y][s] = 0;
	if (s == 0) {
		for (int i = 1; i <= a; ++i) {
			if (i <= x) {
				f[x][y][0] += dp(x-i, y, 1);
				f[x][y][0] %= MOD;
			}
		}
	} else {
		for (int i = 1; i <= b; ++i) {
			if (i <= y) {
				f[x][y][1] += dp(x, y-i, 0);
				f[x][y][1] %= MOD;
			}
		}
	}
	return f[x][y][s];
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d %d %d", &x, &y, &a, &b);
		memset(f, -1, sizeof(f));
		f[0][0][0] = 1;
		f[0][0][1] = 1;
		printf("%d\n", (dp(x, y, 0) + dp(x, y, 1)) % MOD);
	}
	return 0;
}

