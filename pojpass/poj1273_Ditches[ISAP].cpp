#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

/* 最大流SAP算法
 * 邻接矩阵
 * */

const int MAXN = 205;
const int INF = INT_MAX / 2;

int c[MAXN][MAXN], pre[MAXN], que[MAXN], d[MAXN], cnt[MAXN];

int maxflow(int n, int c[][MAXN], int source, int sink, int d[], int que[], int cnt[]) {
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
    int m, n;
    while (EOF != scanf("%d%d", &m, &n)) {
        memset(c, 0, sizeof(c));
        for (int i = 0; i < m; ++i) {
            int a, b, f;
            scanf("%d%d%d", &a, &b, &f);
            c[a-1][b-1] += f;
        }
        int ans = maxflow(n, c, 0, n - 1, d, que, cnt);
		while (ans < 0) ;
        printf("%d\n", ans);
    }
    return 0;
}

