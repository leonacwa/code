#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

/* 邻接矩阵 SAP 
 * 时间复杂度：O(n*m^2)
 * 下标从0开始，直到n-1，共n个点
 * 传入：节点个数n，源点source, 汇点sink, 距离数组d，队列que
 * 返回：最大流
 * gap优化有问题，有些题过不了，所以这个版本把Gap优化去掉了。
 * gap优化：因为长度为L的路径，则必定存在距汇点sink为L, L-1, L-2, ..., 0的点，如果在[0, L]里有一个距离没有电满足，则存在断层，则可直接退出。
 * */

const int MAXN = 305;
const int INF = INT_MAX / 2;

int c[MAXN][MAXN], pre[MAXN], que[MAXN], d[MAXN];

int maxflow(int n, int c[][MAXN], int source, int sink, int d[], int que[]) {
	int *front = que, *tail = que;
	for (int i = 0; i <= n; ++i) d[i] = -1;
	*tail++ = sink;
	d[sink] = 0;
	while (front < tail) {
		int v = *front++;
		for (int u = 0; u < n; ++u) {
			if (d[u] == -1 && c[u][v] > 0) {
				d[u] = d[v] + 1;
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
			d[u] = n + 1;
			for (int i = 0; i < n; ++i) {
				if (c[u][i] > 0 && d[u] > d[i] + 1) d[u] = d[i] + 1;
			}
			if (u != source) u = pre[u];
		}
	}
	return flow;
}

