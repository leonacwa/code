#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = INT_MAX / 2;
int ma[51][51][51];
int f[51][51][51];

int main()
{
	int n, m, r;
	while (EOF != scanf("%d %d %d", &n, &m, &r)) {
		fill((int*)ma, ((int*) ma) + sizeof(ma) / sizeof(int), INF);
		fill((int*)f, ((int*) f) + sizeof(f) / sizeof(int), INF);
		for (int i = 0; i < m; ++i) {
			for (int a = 0; a < n; ++a) {
				for (int b = 0; b < n; ++b) {
					scanf("%d", &ma[i][a][b]);
				}
			}
			for (int k = 0; k < n; ++k) {
				for (int a = 0; a < n; ++a) {
					for (int b = 0; b < n; ++b) {
						if (ma[i][a][b] > ma[i][a][k] + ma[i][k][b]) {
							ma[i][a][b] = ma[i][a][k] + ma[i][k][b];
						}
					}
				}
			}
			for (int a = 0; a < n; ++a) {
				for (int b = 0; b < n; ++b) {
					if (f[0][a][b] > ma[i][a][b]) {
						f[0][a][b] = ma[i][a][b];
					}
				}
			}
		}
		for (int t = 1; t <= n; ++t) {
			for (int k = 0; k < n; ++k) {
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < n; ++j) {
						if (f[t][i][j] > f[t-1][i][k] + f[0][k][j]) {
							f[t][i][j] = f[t-1][i][k] + f[0][k][j];
						}
					}
				}
			}
		}
		while (r--) {
			int s, t, k;
			scanf("%d %d %d", &s, &t, &k);
			--s, --t;
			if (k > n) k = n;
			printf("%d\n", f[k][s][t]);
		}
	}
	return 0;
}

