/* poj 1966 Cable TV Network
 * */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <iostream>
using namespace std;

const int MAXN = 205;
const int INF = INT_MAX / 2;

int mc[MAXN][MAXN];
int c[MAXN][MAXN], que[MAXN], d[MAXN];

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
			for (u = 0; u < n; ++u) {
				if (d[u] == -1 && c[u][v] > 0) {
					d[u] = d[v] + 1;
					*tail++ = u;
				}
			}
			if (d[source] != -1) break;;
		}
		if (d[source] == -1) break;;
		while (ret = dinic_dfs(n, c, sink, d, source, INF)) flow += ret;
	}
	return flow;
}

int main()
{
	int n, m, n2;
	while (EOF != scanf("%d%d", &n, &m)) {
		n2 = n * 2;
		memset(mc, 0,  sizeof(mc));
		for (int i = 0; i < n; ++i) mc[i][i+n] = 1;
		for (int i = 0, a, b; i < m; ++i) {
			scanf(" (%d,%d)", &a, &b);
			mc[a+n][b] = INF;
			mc[b+n][a] = INF;
		}
		int ans = n;
		for (int i = 1, t; i < n; ++i) {
			for (int j = 0; j <= n2; ++j) {
				for (int k = 0; k <= n2; ++k) c[j][k] = mc[j][k];
			}
			t = maxflow(n2, n, i);
			if (ans > t) ans = t;
		}
		if (ans > n || n - ans == 1) ans = n;
		printf("%d\n", ans);
	}
    return 0;
}

