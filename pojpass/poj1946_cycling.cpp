#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <iostream>
using namespace std;

int n, d, e;
int f[21][101][101];

int main()
{
	while (EOF != scanf("%d %d %d", &n, &e, &d)) {
		for (int j = 0; j <= e; ++j) f[1][j][0] = 0;
		for (int k = 1; k <= d; ++k) f[1][0][k] = INT_MAX;

		for (int j = 1; j <= e; ++j) {
			int qj = (int)sqrt((double)j);
			for (int k = 1; k <= d; ++k) {
				f[1][j][k] = INT_MAX;
				for (int p = qj; p >= 1; --p) {
					if (k - p >= 0 && f[1][j - p*p][k - p] < INT_MAX) {
						f[1][j][k] = min(f[1][j][k], f[1][j - p*p][k - p] + 1);
					}
				}
			}
		}

		for (int i = 2; i <= n; ++i) {
			f[i][0][0] = 0;
			for (int j = 1; j <= e; ++j) {
				f[i][j][0] = 0;
				for (int k = 1; k <= d; ++k) {
					f[i][j][k] = INT_MAX;
					for (int p = j; p > 0; --p) {
						if (k - p >= 0 && f[i-1][j-p][k-p] < INT_MAX && f[1][j][p] < INT_MAX) {
							f[i][j][k] = min(f[i][j][k], f[i-1][j-p][k-p] + f[1][j][p]);
						}
					}
				}
			}
		}

		if (f[n][e][d] == INT_MAX) puts("0");
		else printf("%d\n", f[n][e][d]);
	}
	return 0;
}

