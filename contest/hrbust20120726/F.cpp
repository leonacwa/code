#include <cstdio>
#include <cstring>

const int MAXN = 105;
bool mat[MAXN][MAXN], g[MAXN][MAXN];
bool vis[MAXN];
int n;

void dfs(int u, int pu) {
	vis[u] = true;
	for (int i = 1; i <= n; ++i) {
		if (i != pu && g[u][i] && !vis[i]) {
			dfs(i, u);
		}
	}
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		memset(mat, 0, sizeof(mat));
		int u, v;
		while (1) {
			scanf("%d", &u);
			//printf("%d", u);
			if (u == 0) break;
			while ('\n' != getchar()) {
				scanf("%d", &v);
				//printf(" %d", v);
				mat[u][v] = mat[v][u] = true;
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			for (int a = 1; a <= n; ++a) {
				for (int b = 1; b <= n; ++b) {
					g[a][b] = mat[a][b];
				}
			}
			for (int j = 1; j <= n; ++j) { 
				g[i][j] = g[j][i] = false;
			}
			memset(vis, 0, sizeof(vis));
			int u = i + 1;
			if (u > n) u = 1;
			dfs(u, -1);
			int cnt = 0;
			for (int j = 1; j <= n; ++j) {
				if (vis[j]) ++cnt;
			}
			if (cnt != n - 1) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}

