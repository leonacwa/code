/* POJ 1466 Girls and Boys
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 505;

bool mat[MAXN][MAXN];
bool mk[MAXN];
int match[MAXN];

bool dfs(int u, int n) {
	for (int i = 0; i < n; ++i) {
		if (!mk[i] && mat[u][i]) {
			mk[i] = true;
			if (match[i] == -1 || dfs(match[i], n)) {
				match[i] = u;
				return true;
			}
		}
	}
	return false;
}

int maxmatch(int n) {
	int ret = 0;
	memset(match, -1, sizeof(match));
	for (int i = 0; i < n; ++i) {
		memset(mk, 0, sizeof(mk));
		if (dfs(i, n)) ++ret;
	}
	return ret;
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		memset(mat, 0, sizeof(mat));
		for (int i = 0, id, c, d; i < n; ++i) {
			scanf("%d: (%d) ", &id, &c);
			while (c--) {
				scanf("%d", &d);
				mat[id][d] = 1;
				mat[d][id] = 1;
			}
		}
		printf("%d\n", n - maxmatch(n) / 2);
	}
	return 0;
}
