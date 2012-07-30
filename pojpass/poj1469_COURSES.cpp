/* poj 1469 COURSES
 * 二分图最大匹配
 * */

#include <cstdio>
#include <cstring>

const int MAXN = 305;

int n1, n2;
int m1[MAXN], m2[MAXN];
int mat[MAXN][MAXN];
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

int main()
{
	int runs, p, n;
	scanf("%d", &runs);
	while (runs--) {
		memset(mat, 0, sizeof(mat));
		scanf("%d%d", &p, &n);
		for (int i = 0, c, y; i < p; ++i) {
			scanf("%d", &c);
			while (c--) {
				scanf("%d", &y);
				mat[i][y-1] = 1;
			}
		}
		n1 = p, n2 = n;
		int ans = maxmatch();
		if (ans == p) puts("YES");
		else puts("NO");
	}
	return 0;
}
