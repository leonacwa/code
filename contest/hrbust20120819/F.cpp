/* poj 1966 Cable TV Network
 *  *  * */

#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <iostream>
using namespace std;

const int MAXN = 101;
const int INF = INT_MAX / 2;

int mc[MAXN][MAXN];
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
		for (int src = 0; src < n; ++src) {
			for (int i = src+1, t; i < n; ++i) {
				memcpy(c, mc, sizeof(mc));
				t = maxflow(n2, n+src, i);
				if (ans > t) ans = t;
			}
		}
		if (ans > n || n - ans == 1) ans = n;
		printf("%d\n", ans);
	}
	return 0;
}


