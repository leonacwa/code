/*  Paper Presentation
 *  */
#include <cstdio>
#include <cstring>

typedef long long int64;

const int M = 9;

int64 c[M*2][M*2];

int n, m;
int64 f[1<<M];
bool g[M*2][M*2];

char mat[M*2+1][M*2+1];

int64 cnt[M*2], sum[M*2];

int fa[M*2];
int id[M*2];
void init() {
	for (int i = 0; i < 2*M; ++i) fa[i] = i;
}
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) fa[fy] = fx;
}

int dp(int s) {
	if (f[s] >= 0) return f[s];
	f[s] = 0;
	for (int i = 0; i < n; ++i) {
		if (s & (1<<i)) {
			for (int j = 0; j < n; ++j) {
				if (i != j && g[j][i] && !(s&(1<<j))) return 0;
			}
		}
	}
	for (int ss = s, i; ss; ss ^= i) {
		i = ss & -ss;
		f[s] += dp(s ^ i);
	}
	return f[s];
}

int main() {
	memset(c, 0, sizeof(c));
	c[0][0] = 1;
	for (int b = 1; b <= M*2; ++b) {
		c[0][b] = 1;
		for (int a = 1; a <= b; ++a) {
			c[a][b] = c[a][b-1] + c[a-1][b-1];
		}
	}
	int runs, m2;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d", &m);
		m2 = 2 * m;
		init();
		for (int i = 0; i < m2; ++i) {
			scanf("%s", mat[i]);
			for (int j = 0; j < m2; ++j) {
				if (mat[i][j] == 'Y') join(i, j);
			}
		}
		memset(id, -1, sizeof(id));
		int cnt_set = 0;
		bool can = true;
		for (int i = 0; i < m2; ++i) {
			if (id[i] != -1) continue;
			int list[M*2];
			id[i] = 0;
			n = 1;
			list[0] = i;
			for (int j = 0; j < m2; ++j) {
				if (find(i) == find(j) && id[j] == -1) {
					id[j] = n;
					list[n] = j;
					++n;
				}
			}
			cnt[cnt_set] = n;
			if (n <= m) {
				memset(g, 0, sizeof(g));
				for (int j = 0; j < n; ++j) {
					for (int k = 0; k < n; ++k) {
						int a = list[j], b = list[k];
						if (mat[a][b] == 'Y') {
							g[id[b]][id[a]] = true;
						}
					}
				}
				for (int k = 0; k < n; ++k) {
					for (int i = 0; i < n; ++i) {
						for (int j = 0; j < n; ++j) {
							if (g[i][k] && g[k][j] && !g[i][j]) g[i][j] = true;
						}
					}
				}
				memset(f, -1, sizeof(f));
				f[0] = 1;
				sum[cnt_set] = dp((1<<n) - 1);
			} else {
				sum[cnt_set] = 0;
			}
			if (sum[cnt_set] == 0) {
				can = false;
				break;
			}
			/*
			   printf("set %d %d\n", cnt[cnt_set], sum[cnt_set]);
			   for (int i = 0; i < n; ++i) printf("%d ", list[i]);
			   puts("");
			   */
			cnt_set++;
		}

		int64 ans = 0;
		if (can) {
			for (int s = (1<<cnt_set) -1; s; --s) {
				int total = 0, size = 0, list[2*M];
				for (int i = 0; i < cnt_set; ++i) {
					if (!(s & (1<<i))) continue;
					list[size++] = i;
					total += cnt[i];
				}
				if (total != m) continue;
				int64 cs = 1;
				for (int i = 0; i < size; ++i) {
					int li = list[i];
					//			printf("C:%d %d = %d\n", cnt[li], total, C(cnt[li], total));
					cs *= c[cnt[li]][total];
					cs *= sum[li];
				}
				ans += cs;
			}
		}
		printf("%lld\n", ans);
		//puts("....................");
	}
	return 0;
}
