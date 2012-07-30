#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

const int MAXN = 205;
const int INF = INT_MAX / 2;

int c[MAXN][MAXN], pre[MAXN], d[MAXN];
int q[MAXN];

int maxflow(int n, int s, int t) {
	int *front = q, *tail = q;
	memset(d, -1, sizeof(d));
	*tail++ = t;
	d[t] = 0;
	while (front < tail) {
		int v = *front++;
		for (int u = 0; u < n; ++u) {
			if (d[u] == -1 && c[u][v] > 0) {
				d[u] = d[v] + 1;
				*tail++ = u;
			}
		}
	}
	int flow = 0, u = s;
	while (d[s] < n) {
		bool flag = false;
		for (int v = 0; v < n; ++v) {
			if (c[u][v] > 0 && d[u] == d[v] + 1) {
				flag = true;
				pre[v] = u;
				u = v;
				break;
			}
		}
		if (flag) {
			if (u == t) {
				int delta = INF;
				for (; u != s; u = pre[u]) {
					if (c[pre[u]][u] < delta) delta = c[pre[u]][u];
				}
				for (u = t; u != s; u = pre[u]) {
					c[pre[u]][u] -= delta;
					c[u][pre[u]] += delta;
				}
				flow += delta;
				u = s;
			}
		} else {
			d[u] = n + 1;
			for (int i = 0; i < n; ++i) {
				if (c[u][i] > 0 && d[u] > d[i] + 1) d[u] = d[i] + 1;
			}
			if (u != s) u = pre[u];
		}
	}
	return flow;
}

int main()
{
	int m, n;
	while (EOF != scanf("%d%d", &m, &n)) {
		memset(c, 0, sizeof(c));
		for (int i = 0; i < m; ++i) {
			int a, b, f;
			scanf("%d%d%d", &a, &b, &f);
			c[a-1][b-1] += f;
		}
		int ans = maxflow(n, 0, n-1);
		while (ans < 0);
		printf("%d\n", ans);
	}
	return 0; 
}

