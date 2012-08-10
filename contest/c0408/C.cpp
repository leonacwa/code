#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int NN = 205;
int n, m, t;
int a[NN], b[NN];
long long f[2][NN][NN];

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d %d", &n, &m, &t)) {
		for (int i = 1; i <= m; ++i) {
			scanf("%d %d", &a[i], &b[i]);
		}
		long long ans = 0;
		memset(f, -1, sizeof(f));
		f[0][1][0] = 0;
		for (int x = 1; x <= m; ++x) {
			int l = x % 2, ll = (x - 1) % 2;
			for (int i = 1; i <= n; ++i) {
				for (int j = 0; j <= t; ++j) {
					f[l][i][j] = f[ll][i][j];
					if (j > 0) {
						if (i > 1) {
							f[l][i][j] = max(f[l][i][j], f[ll][i-1][j-1]);
						}
						if (i < n) {
							f[l][i][j] = max(f[l][i][j], f[ll][i+1][j-1]);
						}
					}
					if (f[l][i][j] != -1 && a[x] == i) {
						f[l][i][j] += b[x];
					}
				}
			}
		}
		int l = m % 2;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= t; ++j) {
				if (ans < f[l][i][j]) {
					ans = f[l][i][j];
				}
			}
		}
		printf("Scenario #%d\n%lld\n\n", ++nCase, ans);
	}
	return 0;
}

