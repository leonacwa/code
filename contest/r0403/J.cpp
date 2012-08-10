#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

const int NN = 201;
int n, K;
int ma[NN][NN];
int d[NN];
int f[NN][NN];
int opt[NN];

void dp(int r, int pr)
{
	for (int c = 1; c <= n; ++c) {
		if (ma[r][c] == 1 && c != pr) {
			dp(c, r);
		}
	}
	opt[r] = -1;
	for (int j = 1; j <= n; ++j) {
		f[r][j] = d[ma[r][j]];
		for (int c = 1; c <= n; ++c) {
			if (ma[r][c] == 1 && c != pr) {
				f[r][j] += min(f[c][j], f[c][opt[c]] + K);
			}
		}
		if (opt[r] == -1 || f[r][opt[r]] > f[r][j]) {
			opt[r] = j;
		}
	}
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d", &n, &K);
		d[0] = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d", &d[i]);
		}
		memset(ma, -1, sizeof(ma));
		for (int i = 0; i <= n; ++i) ma[i][i] = 0;
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			ma[u][v] = ma[v][u] = 1;
		}
		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					if (ma[i][k] != -1 && ma[k][j] != -1 && (ma[i][j] == -1 || ma[i][j] > ma[i][k] + ma[k][j])) {
						ma[i][j] = ma[i][k] + ma[k][j];
					}
				}
			}
		}
		dp(1, -1);
		int ans = INT_MAX;
		for (int i = 1; i <= n; ++i) {
			if (ans > f[1][i]) ans = f[1][i];
		}
		printf("%d\n", ans + K);
	}
	return 0;
}

