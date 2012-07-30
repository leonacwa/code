/* poj 1087
 * */
#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <map>
#include <string>
using namespace std;


const int MAXN = 505;
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
			d[u] = n - 1;
			for (int i = 0; i < n; ++i) {
				if (c[u][i] > 0 && d[u] > d[i]) d[u] = d[i];
			}
			cnt[++d[u]]++;
			if (u != source) u = pre[u];
			if (cnt[old_du] == 0) break;
		}
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
		printf("%d\n", m - maxflow(tot, 0, 1));
	}
	return 0;
}

