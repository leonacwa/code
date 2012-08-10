#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

/* 最大流 邻接矩阵 SAP 
 * 时间复杂度：O(n*m^2), 速度更快，推荐使用
 * 下标从0开始，直到n-1，共n个点
 * 传入：节点个数n，源点source, 汇点sink, 距离数组d，队列que
 * 返回：最大流
 * gap优化：因为长度为L的路径，则必定存在距汇点sink为L, L-1, L-2, ..., 0的点，如果在[0, L]里有一个距离没有电满足，则存在断层，则可直接退出。
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

