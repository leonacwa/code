/* Sleeping at Work [IDIOPEN 2011]
 * http://acm.hnu.cn/online/?action=problem&type=show&id=12516&courseid=0
 * 动态规划，做的时候少考虑初始条件了
 * */
#include <cstdio>
#include <cstring>

int e[505];
int f[505][55][55];

template <class T>
void check_max(T &a, const T &b) {
	if (a < b) a = b;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, m, r;
		scanf("%d%d%d", &n, &m, &r);
		for (int i = 1; i <= n; ++i) scanf("%d", &e[i]);
		memset(f, -1, sizeof(f));
		for (int i = 0; i <= n; ++i) f[i][0][0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				f[i][j][0] = f[i-1][j][0];
				for (int k = 1; k <= r; ++k) {
					if (f[i-1][j-1][k-1] != -1) check_max(f[i][j][k], f[i-1][j-1][k-1] + k*e[i]);
					if (f[i-1][j][k] != -1) check_max(f[i][j][0], f[i-1][j][k]);
				}
			}
		}
		int ans = -1;
		for (int i = 0; i <= r; ++i) {
			if (f[n][m][i] != -1) check_max(ans, f[n][m][i]);
		}
		if (ans == -1) puts("impossible");
		else printf("%d\n", ans);
	}
	return 0;
}
