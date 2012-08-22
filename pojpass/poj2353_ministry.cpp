#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LLONG;
const int MM = 100;
const int NN = 500;
int m, n;
LLONG ma[MM][NN];
LLONG f[MM][NN];
int opt[MM][NN];
int order[NN*MM];

int main()
{
	while (EOF != scanf("%d %d", &m, &n)) {
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%lld", &ma[i][j]);
			}
		}
		memset(f, -1, sizeof(f));
		for (int i = 0; i < n; ++i) {
			f[0][i] = ma[0][i];
			opt[0][i] = 1;
		}
		for (int i = 1; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				f[i][j] = f[i-1][j] + ma[i][j], opt[i][j] = 1;
			}
			for (int j = 1; j < n; ++j) {
				if (f[i][j] > f[i][j-1] + ma[i][j]) {
					f[i][j] = f[i][j-1] + ma[i][j], opt[i][j] = 2;
				}
			}
			for (int j = n - 2; j >= 0; --j) {
				if (f[i][j] > f[i][j+1] + ma[i][j]) {
					f[i][j] = f[i][j+1] + ma[i][j], opt[i][j] = 3;
				}
			}
		}
		LLONG ans;
		int k = -1;
		for (int i = 0; i < n; ++i) {
			if (k == -1 || ans > f[m-1][i]) {
				ans = f[m-1][i], k = i;
			}
		}
		int cnt = 0, i = m - 1;
		while (i >= 0) {
			order[cnt++] = k + 1;
			if (opt[i][k] == 1) {
				--i;
			} else if (opt[i][k] == 2) {
				--k;
			} else if (opt[i][k] == 3) {
				++k;
			}
		}
		for (int i = cnt - 1; i >= 0; --i) {
			printf("%d\n", order[i]);
		}
	}
	return 0;
}

