#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;
const int MAXN =  505;
int a[MAXN][MAXN];
int s[MAXN][MAXN];
int o[2][MAXN][MAXN];

/*
inline int BLOCK(int lx, int ly, int hx, int hy) {
	return s[hx][hy] - s[lx-1][hy] - s[hx][ly-1] + s[lx-1][ly-1];
}
*/
#define BLOCK(lx, ly, hx, hy) (s[hx][hy] - s[lx-1][hy] - s[hx][ly-1] + s[lx-1][ly-1])

int main()
{
	int n, m;
	while (2 == scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &a[i][j]);
				o[1][i][j] = a[i][j];
				s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
			}
		}
		int l = min(n, m);
		int ans = -INT_MAX;
		int c = 0;
		for (int k = 3; k <= l; k += 2) {
			for (int i = 1; i+k-1 <= n; ++i) {
				for (int j = 1; j+k-1 <= m; ++j) {
					o[c][i][j] = BLOCK(i, j, i + k - 1, j + k - 1) - a[i+1][j] - o[1-c][i+1][j+1];
					if (ans < o[c][i][j]) {
						ans = o[c][i][j];
					}
				}
			}
			c = 1 - c;
		}
		printf("%d\n", ans);
	}
	return 0;
}

