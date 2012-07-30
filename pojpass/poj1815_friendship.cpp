/* poj 1815 Friendship
 * 无向图求最小连通度，并且输出去掉的点
 * 无向图转为有向图最大流的解法
 * */
#include <cstdio>
#include <cstring>
#include <climits>

const int MAXN = 505;
const int INF = INT_MAX / 3;

int mat[MAXN][MAXN], flow[MAXN][MAXN];
int d[MAXN], que[MAXN];
int vset[MAXN];

int dinic_dfs(int n, int sink, int u, int f) {
	if (u == sink) return f;
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		if (d[u] == d[i] + 1 && mat[u][i] > flow[u][i]) {
			int t = mat[u][i] - flow[u][i];
			if (ret = dinic_dfs(n, sink, i, f < t ? f : t)) {
				flow[u][i] += ret;
				flow[i][u] -= ret;
				return ret;
			}
		}
	}
	return 0;
}

bool dinic_bfs(int n, int source, int sink) {
	int *fr = que, *ta = que;
	for (int i = 0; i < n; ++i) d[i] = n;
	d[sink] = 0;
	*ta++ = sink;
	while (fr < ta) {
		int v = *fr++;
		for (int i = 0; i < n; ++i) {
			if (d[i] == n && mat[i][v] > flow[i][v]) {
				d[i] = d[v] + 1;
				if (i == source) return true;
				*ta++ = i;
			}
		}
	}
	return false;
}

int maxflow(int n, int source, int sink) {
	int f = 0, ret;
	while (dinic_bfs(n, source, sink)) {
		while (ret = dinic_dfs(n, sink, source, INF)) f += ret;
	}
	return f;
}

int main()
{
	int n, s, t;
	while (EOF != scanf("%d%d%d", &n, &s, &t)) {
		int tot = n * 2 + 2, source = 0, sink = n*2 + 1;
		memset(flow, 0, sizeof(flow));
		memset(mat, 0, sizeof(mat));
		mat[source][s] = mat[t][sink] = INF;
		for (int i = 1; i <= n; ++i) {
			mat[i][i+n] = 1;
			for (int j = 1, v; j <= n; ++j) {
				scanf("%d", &v);
				if (v) mat[i+n][j] = INF;
			}
		}
		mat[s][s+n] = mat[t][t+n] = INF;
		if (mat[s+n][t]) puts("NO ANSWER!");
		else {
			int ans = maxflow(tot, source, sink);
			printf("%d\n", ans);
			if (ans == 0) break;
			int cnt = 0, tmp = ans;
			for (int i = 1; i <= n; ++i) {
				if (i == s || i == t) continue;
				if (flow[i][i+n] == 0) continue;
				memset(flow, 0, sizeof(flow));
				mat[i][i+n] = 0;
				int tmp2 = maxflow(tot, source, sink);
				if (tmp2 != tmp) {
					vset[cnt++] = i;
					tmp = tmp2;
				} else mat[i][i+n] = 1;
			}
			for (int i = 0; i < cnt-1; ++i) printf("%d ", vset[i]);
			printf("%d\n", vset[cnt-1]);
		}
	}
	return 0;
}

