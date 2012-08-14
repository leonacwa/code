/* Ombrophobic Bovines
 * 最大流 + 二分
 * */
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int64;
const int MAXN = 505;
const int64 INF = LLONG_MAX / 3;

int cow[MAXN], contain[MAXN];
int64 mat[MAXN][MAXN];
int64 dis[MAXN*MAXN];

int c[MAXN][MAXN], que[MAXN], d[MAXN];

int dinic_dfs(int n, int sink, int u, int f) {
	if (u == sink) return f;
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		if (d[u] == d[i] + 1 && c[u][i] > 0) {
			int t = dinic_dfs(n, sink, i, c[u][i] < f ? c[u][i] : f);
			if (t) {
				ret += t, f -= t, c[u][i] -= t,	c[i][u] += t;
			}
		}
		if (f == 0) break;
	}
	return ret;
}
int maxflow(int n, int source, int sink) {
	int flow = 0, ret, u, v, *fr, *ta;
	while (1) {
		for (int i = 0; i <= n; ++i) d[i] = -1;
		fr = ta = que;
		*ta++ = sink;
		d[sink] = 0;
		while (fr < ta) {
			v = *fr++;
			for (u = 0; u < n; ++u) {
				if (d[u] == -1 && c[u][v] > 0) {
					d[u] = d[v] + 1; *ta++ = u;
				}
			}
		}
		if (d[source] == -1) break;;
		while ((ret = dinic_dfs(n, sink, source, INT_MAX))) flow += ret;
	}
	return flow;
}


int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		int tot = n + n + 2, source = 0, sink = n+n+1, total = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", cow + i, contain + i);
			total += cow[i];
		}
		for (int i = 1; i <= n; ++i) {
			mat[i][i] = 0;
			for (int j = i+1; j <= n; ++j)
				mat[i][j] = mat[j][i] = INF;
		}
		for (int i = 0, a, b, w; i < m; ++i) {
			scanf("%d%d%d", &a, &b, &w);
			if (mat[a][b] > w) {
				mat[a][b] = mat[b][a] = w;
			}
		}
		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) {
				if (mat[i][k] == INF) continue;
				for (int j = i+1; j <= n; ++j) {
					if (mat[k][j] == INF) continue;
					if (mat[i][j] > mat[i][k] + mat[k][j]) mat[i][j] = mat[j][i] = mat[i][k] + mat[k][j];
				}
			}
		}
		int cnt = 0;
		for (int i = 1; i <= n; ++i) for (int j = i; j <= n; ++j) dis[cnt++] = mat[i][j];
		sort(dis, dis + cnt);
		int64 * end = unique(dis, dis + cnt);
		cnt = end - dis;
		dis[cnt] = INF;
		int l = 0, r = cnt;
		while (l < r) {
			int m = (l + r) >> 1;
			memset(c, 0, sizeof(c));
			for (int i = 1; i <= n; ++i) {
				c[source][i] = cow[i];
				c[i+n][sink] = contain[i];
				c[i][i+n] = INT_MAX / 2;
				for (int j = 1; j <= n; ++j) {
					if (i != j && mat[i][j] <= dis[m]) {
						c[i][j+n] = INT_MAX / 2;
					}
				}
			}
			int flow = maxflow(tot, source, sink);
			if (total == flow) {
				r = m;
			} else {
				l = m + 1;
			}
		}
		int64 ans = -1;
		if (dis[l] < INF) ans = dis[l];
		printf("%lld\n", ans);
	}
	return 0;
}
