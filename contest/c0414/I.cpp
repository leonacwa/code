#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
int f[105][55][2];
int g[105][55][2];
char s[105];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%s", s);
		scanf("%d", &k);
		int ls = strlen(s);
		for (int i = 0; i <= ls; ++i) {
			for (int j = 0; j <= k; ++j) {
				for (int l = 0; l <= 1; ++l) {
					f[i][j][l] = -INT_MAX / 2;
					g[i][j][l] = INT_MAX / 2;
				}
			}
		}
		f[0][0][0] = g[0][0][0] = 0;
		for (int i = 1; i <= ls; ++i) {
			for (int j = 0; j <= k; ++j) {
				for (int l = 0; l <= 1; ++l) {
					for (int m = 0; m <= j; ++m) {
						if ((m & 1) ^ (s[i-1] == 'F')) {
							f[i][j][l] = max(f[i][j][l], f[i-1][j-m][l] + (l ? -1 : 1));
							g[i][j][l] = min(g[i][j][l], g[i-1][j-m][l] + (l ? -1 : 1));
						} else {
							f[i][j][l] = max(f[i][j][l], f[i-1][j-m][!l]);
							g[i][j][l] = min(g[i][j][l], g[i-1][j-m][!l]);
						}
					}
				}
			}
		}
		printf("%d\n", max(max(f[ls][k][0], f[ls][k][1]), abs(min(g[ls][k][0], g[ls][k][1]))));
	}
	return 0;
}

