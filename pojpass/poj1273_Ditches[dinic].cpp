#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

/* 最大流dinic算法
 * 递归版本
 * 时间复杂度 O(V^2*E)
 * 邻接矩阵
 * */

const int MAXN = 205;
const int INF = INT_MAX / 2;

int c[MAXN][MAXN], que[MAXN], d[MAXN];

// 节点个数n，图c[][]， 汇点sink，距离d[]，出发点u，流f
int dinic_dfs(int n, int c[][MAXN], int sink, int d[], int u, int f) {
	if (u == sink) return f;
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		if (d[u] == d[i] + 1 && c[u][i] > 0) {
			int t = dinic_dfs(n, c, sink, d, i, c[u][i] < f ? c[u][i] : f);
			ret += t;
			f -= t;
			c[u][i] -= t;
			c[i][u] += t;
		}
	}
	return ret;
}
// 节点个数n，图c[][]， 源点source，汇点sink，距离d[]，队列que[]
int max_flow(int n, int c[][MAXN], int source, int sink, int d[], int que[]) 
{
	int flow = 0;
	while (1) {
		for (int i = 0; i <= n; ++i) d[i] = -1;
		int u, v, *front = que, *tail = que;
		*tail++ = sink;
		d[sink] = 0;
		while (front < tail) {
			v = *front++;
			for (u = 0; u < n; ++u) {
				if (d[u] == -1 && c[u][v] > 0) {
					d[u] = d[v] + 1;
					*tail++ = u;
				}
			}
			if (d[source] != -1) break;;
		}
		if (d[source] == -1) break;;
		flow += dinic_dfs(n, c, sink, d, source, INF);
	}
	return flow;
}

int main()
{
	int m, n;
	while (EOF != scanf("%d%d", &m, &n))
	{
		memset(c, 0, sizeof(c));
		for (int i = 0; i < m; ++i)
		{
			int a, b, f;
			scanf("%d%d%d", &a, &b, &f);
			c[a-1][b-1] += f;
		}
		int ans = max_flow(n, c, 0, n - 1, d, que);
		printf("%d\n", ans);
	}
	return 0;
}

