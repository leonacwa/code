/* Just Another Information Sharing Problem
 * 构图转成最大流的解决
 * */
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 505;
const int INF = 99999999;

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

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		map<int, int> ma;
		int source = 0, sink;
		int m_cnt = n;
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; ++i) {
			int ai, bi, ci;
			scanf("%d%d%d", &ai, &bi, &ci);
			c[source][i] = ci;
			for (int j = 0, t; j < ai; ++j) {
				scanf("%d", &t);
				int k = ma[t];
				if (k == 0) {
					k = ma[t] = ++m_cnt;
				}
				c[i][k] = 1;
			}
		}
		sink = m_cnt + 1;
		for (int i = n+1; i <= m_cnt; ++i) {
			c[i][sink] = 1;
		}
		int q;
		scanf("%d", &q);
		c[source][q] = INF;
		int ans = maxflow(m_cnt + 2,  source, sink);
		printf("%d\n", ans);
	}
	return 0;
}
