/* poj 3308 Paratroopers
 * 各个数的乘法运算转换成加法运算，使用对数log()  exp()
 * */
#include <cstdio>
#include <cstring>
#include <climits>
#include <cmath>
#include <cfloat>

const int MAXN = 205;
const double INF = DBL_MAX / 2;
const double eps = 1e-8;

double c[MAXN][MAXN];
int pre[MAXN], que[MAXN], d[MAXN], cnt[MAXN];

double maxflow(int n, int source, int sink) {
	int *front = que, *tail = que;
	for (int i = 0; i < n; ++i) d[i] = n, cnt[i] = 0;
	d[sink] = 0;
	cnt[n] = n - 1;
	cnt[0]++;
	*tail++ = sink;
	while (front < tail) {
		int v = *front++;
		for (int u = 0; u < n; ++u) {
			if (d[u] >= n && c[u][v] > eps) {
				d[u] = d[v] + 1;
				cnt[n]--;
				cnt[d[u]]++;
				*tail++ = u;
			}
		}
	}
	double flow = 0;
	int u = source;
	while (d[source] < n) {
		bool flag = false;
		for (int v = 0; v < n; ++v) {
			if (c[u][v] > eps && d[u] == d[v] + 1) {
				flag = true;
				pre[v] = u;
				u = v;
				break;
			}
		}
		if (flag) {
			if (u == sink) {
				double delta = INF;
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
				if (c[u][i] > eps && d[u] > d[i]) d[u] = d[i];
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
	int runs, m, n, l, sink, tot;
	double f;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d%d%d", &m, &n, &l);
		sink = m + n + 1;
		tot = m + n + 2;
		for (int i = 0; i < tot; ++i) for (int j = 0; j < tot; ++j) c[i][j] = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%lf", &f);
			c[0][i] = log(f);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%lf", &f);
			c[m+i][sink] = log(f);
		}
		for (int i = 0, a, b; i < l; ++i) {
			scanf("%d%d", &a, &b);
			c[a][b+m] = INF;
		}
		printf("%.4f\n", exp(maxflow(tot, 0, sink)));
	}
	return 0;
}
