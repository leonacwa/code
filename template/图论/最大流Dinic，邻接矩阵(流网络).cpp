/* 最大流Dinic算法
 * 邻接矩阵
 * 时间复杂度：O(V^2*E)
 * 含流网络
 * */
#include <cstdio>
#include <cstring>
#include <climits>

const int MAXN = 505;
const int INF = INT_MAX / 3;

int mat[MAXN][MAXN], flow[MAXN][MAXN]; // mat[][]是网络，flow[][]是流网络
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
	return 0;
}

