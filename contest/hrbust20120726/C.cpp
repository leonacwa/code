#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

const int MAXN = 205;
const int INF = INT_MAX / 2;

int c[MAXN][MAXN], que[MAXN], d[MAXN];

// 节点个数n，图c[][]， 汇点sink，距离d[]，出发点u，流f
int dinic_dfs(int n, int sink, int u, int f) {
	if (u == sink) return f;
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		if (d[u] == d[i] + 1 && c[u][i] > 0) {
			int t = dinic_dfs(n, sink, i, c[u][i] < f ? c[u][i] : f);
			ret += t;
			f -= t;
			c[u][i] -= t;
			c[i][u] += t;
		}
	}
	return ret;
}
// 节点个数n，图c[][]， 源点source，汇点sink，距离d[]，队列que[]
int maxflow(int n, int source, int sink) 
{
	int flow = 0, ret;
	while (1) {
		for (int i = 0; i <= n; ++i) d[i] = -1;
		int u, v, *front = que, *tail = que;
		*tail++ = sink;
		d[sink] = 0;
		while (front < tail) {
			v = *front++;
			for (u = 1; u <= n; ++u) {
				if (d[u] == -1 && c[u][v] > 0) {
					d[u] = d[v] + 1;
					*tail++ = u;
				}
			}
			if (d[source] != -1) break;;
		}
		if (d[source] == -1) break;;
		while (ret = dinic_dfs(n, sink, source, INF)) flow += ret;
	}
	return flow;
}

int main()
{
	int n, m, d;
	while (EOF != scanf("%d%d%d", &n, &m, &d)) {
		memset(c, 0, sizeof(c));
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			c[a][b]++;
			c[b][a]++;
		}
		int ans = maxflow(n, 1, n);
		if (ans >= d) puts("Orz!");
		else puts("Jiao Zhu v5!");
	}
	return 0;
}

