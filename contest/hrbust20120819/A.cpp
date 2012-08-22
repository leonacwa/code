#include <cstdio>
#include <cstring>

const int MAXN = 205;

int n1, n2;
int m1[MAXN], m2[MAXN];
bool mat[MAXN][MAXN];
bool mk[MAXN];

bool dfs(int u) {
	for (int i = 0; i < n2; ++i) {
		if (mat[u][i] && !mk[i]) {
			mk[i] = true;
			if (m2[i] == -1 || dfs(m2[i])) {
				m2[i] = u;
				m1[u] = i;
				return true;
			}
		}
	}
	return false;
}

int maxmatch() {
	int ret = 0;
	memset(m1, -1, sizeof(m1[0])*n1);
	memset(m2, -1, sizeof(m2[0])*n2);
	for (int i = 0; i < n1; ++i) {
		if (m1[i] == -1) {
			memset(mk, 0, sizeof(mk[0]) * n2);
			if (dfs(i)) ++ret;
		}
	}
	return ret;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, m;
		scanf("%d%d", &n, &m);
		memset(mat, 1, sizeof(mat));
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			--a, --b;
			mat[a][b] = mat[b][a] = false;
		}
		n1 = n2 = n;
		int ans = maxmatch();
		printf("maxmatch %d\n", ans);
		for (int i = 0; i < n; ++i) {
			if (m1[i] != -1) {
				for (int j = 0; j < n; ++j) {
					if (mat[j][m1[i]] == false && m1[j] == -1) {
						printf("%d no %d\n", j, m1[i]);
						m1[i] = -1;
						--ans;
						break;
					}
				}
			}
		}
		if (ans < 0) ans = 0;
		if (ans > n / 2) ans = n / 2;
		printf("%d\n", ans);
	}
	return 0;
}
