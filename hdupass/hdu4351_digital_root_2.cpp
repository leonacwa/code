/* Digital root
 * 离线算法
 * 测试数据：
3
5
101 240 331 4 52
3
1 3
4 5
1 5
5
101 240 331 4 52
3
1 3
4 5
1 5
5
9 9 9 9 9
3
1 3
4 5
1 5

 * */
#include <cstdio>
#include <cstring>

const int MAXN = 100005;

int a[MAXN], s[MAXN], l[MAXN][10], r[MAXN][10];

int main() {
	int runs;
	scanf("%d", &runs);
	for (int run = 1; run <= runs; ++run) {
		int n, q;
		scanf("%d", &n);
		s[0] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			a[i] = (a[i] - 1) % 9 + 1;
			s[i] = (s[i-1] + a[i] - 1) % 9 + 1;
		}
		memset(r, -1, sizeof(r));
		memset(l, -1, sizeof(l));
		r[1][a[1]] = 1;
		for (int i = 2; i <= n; ++i) {
			r[i][a[i]] = i;
			for (int k = 0; k <= 9; ++k) {
				if (r[i-1][k] == -1) continue;
				int t = (k + a[i] - 1) % 9 + 1;
				if (r[i][t] == -1 || r[i][t] < r[i-1][k]) {
					r[i][t] = r[i-1][k];
				}
			}
		}
		l[n][a[n]] = n;
		for (int i = n-1; i >= 1; --i) {
			l[i][a[i]] = i;
			for (int k = 0; k <= 9; ++k) {
				if (l[i+1][k] == -1) continue;
				int t = (k + a[i] - 1) % 9 + 1;
				if (l[i][t] == -1 || l[i][t] > l[i+1][k]) {
					l[i][t] = l[i+1][k];
				}
			}
		}
		scanf("%d", &q);
		printf("Case #%d:\n", run);
		while (q--) {
			int a, b, cnt = 0, m;
			scanf("%d%d", &a, &b);
			m = (9 + s[b] - s[a-1] - 1) % 9 + 1;
			//printf("[%d, %d] %d\n", a, b, m);
			for (int i = 9; i >= 0 && cnt < 5; --i) {
				if (l[a][i] <= b && l[a][i] != -1) {
					if (cnt) printf(" ");
					++cnt;
					printf("%d", i);
					continue;
				}
				if (a <= r[b][i] && r[b][i] != -1) {
					if (cnt) printf(" ");
					++cnt;
					printf("%d", i);
					continue;
				}
				for (int j = 0, t, u; j <= 9; ++j) {
					t = (18 + m - i - j - 1) % 9 + 1;
					u = l[a][j] + 1;
					if (l[a][j] != -1 && r[b][t] != -1 && l[a][j]+1 < r[b][t] && l[u][i] != -1 && l[u][i] < b) {
						if (cnt) printf(" ");
						++cnt;
						printf("%d", i);
				//		printf("[%d:%d %d, %d:%d %d]", a, j, l[a][j], b, t, r[b][t]);
						break;
					}
				}
			}
			for (; cnt < 5; ++cnt) {
				if (cnt) printf(" ");
				printf("-1");
			}
			puts("");
		}
		if (run < runs) puts("");
	}
	return 0;
}
