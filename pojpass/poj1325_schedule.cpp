/*poj1325 Machein Schedule
 * 二分图最大匹配
 * 二分图：点覆盖数 = 匹配数
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 105;

int m1[MAXN], m2[MAXN];
int mat[MAXN][MAXN];
// hungary 算法
int maxmatch(int n1, int n2, int mat[][MAXN], int m1[], int m2[]) { // BFS找增广路
	int p, q, s[MAXN], t[MAXN], ret = 0, i, j, k;
	memset(m1, -1, sizeof(m1[0])*n1);
	memset(m2, -1, sizeof(m2[0])*n2);
	for (i = 0; i < n1; ++i) {
		memset(t, -1, sizeof(t[0])*n2);
		for (s[p=q=0] = i; p <= q && m1[i] < 0 ; ++p) {
			for (k = s[p], j = 0; j < n2 && m1[i] < 0; ++j) {
				if (mat[k][j] && t[j] < 0) {
					s[++q] = m2[j], t[j] = k;
					if (s[q] < 0) {
						for (p = j; p >= 0; j = p) {
							m2[j] = k = t[j];
							p = m1[k];
							m1[k] = j;
						}
					}
				}
			}
		}
		if (m1[i] >= 0) ++ret;
	}
	return ret;
}

int main()
{
	int n, m, k;
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		scanf("%d%d", &m, &k);
		memset(mat, 0, sizeof(mat));
		while (k--) {
			int i, x, y;
			scanf("%d%d%d", &i, &x, &y);
			if (x * y) mat[x][y] = 1; // 0 模式下无需转换
		}
		int ans = maxmatch(n, m, mat, m1, m2);
		printf("%d\n", ans);
	}
	return 0;
}

