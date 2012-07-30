/* POJ 2125 Destroying The Graph
 * */

#include <cstdio>
#include <cstring>
#include <climits>

const int MAXN = 305;
const int INF = INT_MAX / 2;

int c[MAXN][MAXN], pre[MAXN], que[MAXN], d[MAXN], cnt[MAXN];

int maxflow(int n, int source, int sink) {
	int *front = que, *tail = que;
	for (int i = 0; i < n; ++i) d[i] = n, cnt[i] = 0;
	d[sink] = 0;
	cnt[n] = n - 1;
	cnt[0]++;
	*tail++ = sink;
	while (front < tail) {
		int v = *front++;
		for (int u = 0; u < n; ++u) {
			if (d[u] >= n && c[u][v] > 0) {
				d[u] = d[v] + 1;
				cnt[n]--;
				cnt[d[u]]++;
				*tail++ = u;
			}
		}
	}
	int flow = 0, u = source;
	while (d[source] < n) {
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
			if (u == sink) {
				int delta = INF;
				for (u = sink; u != source; u = pre[u]) {
					if (c[pre[u]][u] < delta) delta = c[pre[u]][u];
				}
				for (u = sink; u != source; u = pre[u]) {
					c[pre[u]][u] -= delta;
					c[u][pre[u]] += delta;
				}
				flow += delta;
				u = source;
			}
		} else {
			int old_du = d[u];
			cnt[old_du]--;
			d[u] = n - 1;
			for (int i = 0; i < n; ++i) {
				if (c[u][i] > 0 && d[u] > d[i]) d[u] = d[i];
			}
			++d[u];
			cnt[d[u]]++;
			if (u != source) u = pre[u];
			if (cnt[old_du] == 0) break;
		}
	}
	return flow;
}

bool vis[MAXN];
int ans[MAXN*2];
void dfs(int u, int n) {
	vis[u] = true;
	for (int i = 0; i < n; ++i) {
		if (!vis[i] && c[u][i] > 0) {
			dfs(i, n);
		}
	}
}

int main()
{
	int n, m, sink, source, tot;
	while (EOF != scanf("%d%d", &n, &m)) {
		source = 0, sink = n + n + 1, tot = n + n + 2;
		memset(c, 0, sizeof(c));
		for (int i = 1, t; i <= n; ++i) {
			scanf("%d", &t);
			c[i+n][sink] = t;
		}
		for (int i = 1, t; i <= n; ++i) {
			scanf("%d", &t);
			c[source][i] = t;
		}
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			c[a][b+n] = INF;
		}
		int mf = maxflow(tot, source, sink);
		memset(vis, 0, sizeof(vis));
		dfs(source, tot);
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (!vis[i]) ans[cnt++] = i;
			if (vis[i+n]) ans[cnt++] = i + n;
		}
		printf("%d\n%d\n", mf, cnt);
		for (int i = 0; i < cnt; ++i) {
			if (ans[i] <= n) printf("%d -\n", ans[i]);
			else printf("%d +\n", ans[i] - n);
		}
	}
	return 0;
}
