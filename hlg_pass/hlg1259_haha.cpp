#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int NN = 17;
bool g[NN][NN];
long long f[1 << 17];
int n, m;

long long dp(int s)
{
	long long &sum = f[s];
	if (sum >= 0) return sum;
	for (int i = 0; i < n; ++i) {
		if (s & (1 << i)) {
			for (int j = 0; j < n; ++j) {
				if (i != j && g[j][i] && !(s & (1 << j))) return sum = 0;
			}
		}
	}
	sum = 0;
	for (int ss = s, i; ss; ss ^= i) {
		i = ss & -ss;
		sum += dp(s ^ i);
	}
	return sum;
}

int main()
{
	while (EOF != scanf("%d %d", &n, &m)) {
		memset(g, 0, sizeof(g));
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d %d", &a, &b);
			g[a-1][b-1] = true;
		}
		for(int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (g[i][k] && g[k][j]) g[i][j] = true;
				}
			}
		}
		int i;
		for (i = 0; i < n; ++i) {
			if (g[i][i]) break;
		}
		if (i < n) {
			puts("0");
			continue;
		}
		memset(f, -1, sizeof(f[0])*(1<<n));
		f[0] = 1;
		printf("%lld\n", dp((1<<n) - 1));
	}
	return 0;
}

