/* Destroying the bus stations
 * 顶点个数最多50个，思路：暴搜，优化：IDA，从小到大枚举最多的去掉的点数。
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 55, INF = 99999999;

int n, m, k, min_cut;

bool mat[MAXN][MAXN];
int d[MAXN];
bool in[MAXN];
int pre[MAXN], que[MAXN];

int bfs(int &ns, int s[]) {
	for (int i = 1; i <= n; ++i) d[i] = INF;
	d[1] = 0;
	pre[1] = 1;
	int *fr = que, *ta = que, *ta2;
	*ta++ = 1;
	while (fr < ta) {
		ta2 = ta;
		while (fr < ta) {
			int i = *fr++;
			for (int j = 1; j <= n; ++j) {
				if (in[j] && mat[i][j] && d[j] > d[i] + 1) {
					*ta2++ = j;
					d[j] = d[i] + 1;
					pre[j] = i;
				}
			}
		}
		ta = ta2;
	}
	ns = 0;
	for (int i = pre[n]; i != 1; i = pre[i]) {
		s[ns++] = i;
	}
	return d[n];
}

bool dfs(int sum) {
	int ns, s[MAXN];
	if (bfs(ns, s) > k) return true;
	if (sum < min_cut) {
		for (int i = 0; i < ns; ++i) {
			in[s[i]] = 0;
			if (dfs(sum+1)) return true;
			in[s[i]] = 1;
		}
	}
	return false;
}

int main() {
	while (EOF != scanf("%d%d%d", &n, &m, &k)) {
		if (n == 0 && m == 0 && k == 0) break;
		memset(mat, 0, sizeof(mat));
		for (int i = 0, s, f; i < m; ++i) {
			scanf("%d%d", &s, &f);
			mat[s][f] = 1;
		}
		memset(in, 1, sizeof(in));
		for (min_cut = 0; min_cut < n; ++min_cut) {
			if (dfs(0)) break;
		}
		printf("%d\n", min_cut);
	}
	return 0;
}
