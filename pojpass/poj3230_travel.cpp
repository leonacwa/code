#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;
const int NN = 101;

int exp[NN][NN];
int inc[NN][NN];
int f[NN][NN];

int main()
{
	int n, m;
	while (EOF != scanf("%d %d", &n, &m)) {
		if (n == 0 && m == 0) break;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &exp[i][j]);
			}
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &inc[i][j]);
			}
		}
		memset(f, 0, sizeof(f));
		for (int i = 0; i < n; ++i) {
			f[0][i] = inc[0][i] - exp[0][i];
		}
		for (int i = 1; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				f[i][j] = -INT_MAX;
				for (int k = 0; k < n; ++k) {
					f[i][j] = max(f[i][j], f[i-1][k] + inc[i][j] - exp[k][j]);
				}
			}
		}
		int ans = -INT_MAX;
		for (int i = 0; i < n; ++i) {
			ans = max(ans, f[m-1][i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}

