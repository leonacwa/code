/* poj 1087
 * */
#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <map>
#include <string>
using namespace std;

/* 最大流dinic算法
 * 递归版本
 * 时间复杂度 O(V^2*E)
 * 邻接矩阵
 * */

const int MAXN = 505;
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
int maxflow(int n, int c[][MAXN], int source, int sink, int d[], int que[]) 
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
	int n, m, k;
	char str1[32], str2[32];
	while (EOF != scanf("%d", &n)) {
		map<string, int> ma;
		memset(c, 0, sizeof(c));
		int tot = 2;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str1);
			int v = tot++;
			ma[str1] = v;
			c[0][v] = 1;
		}
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) {
			scanf("%s%s", str1, str2);
			int u = ma[str2], v = tot++;
			if (u == 0) u = ma[str2] = tot++;
			ma[str1] = v;
			c[u][v]++;
			c[v][1]++;
		}
		scanf("%d", &k);
		for (int i = 1; i <= k; ++i) {
			scanf("%s%s", str1, str2);
			int u = ma[str2], v = ma[str1];
			if (u == 0) u = ma[str2] = tot++;
			if (v == 0) v = ma[str1] = tot++;
			c[u][v] = INF;
		}
		printf("%d\n", m - maxflow(tot, c, 0, 1, d, que));
	}
	return 0;
}

