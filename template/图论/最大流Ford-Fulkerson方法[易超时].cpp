#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

/* Ford-Fulkerson算法
 * 邻接矩阵
 * 残余网络
 * !!!!!!  容易超时，慎重
 * */

const int MAXN = 205;
const int INF = INT_MAX / 2;

int c[MAXN][MAXN], pre[MAXN], q[MAXN];

int maxflow(int n, int c[][MAXN], int source, int sink)
{
    if (source == sink) return INF;
	int flow = 0, u, i, j, delta, p, q, que[MAXN];
    for (;;) {
        for (i = 0; i < n; pre[i++] = 0);
		u = source;
        pre[u] = source + 1;
		delta = INF;
        for (p = q = 0; p <= q && !pre[sink]; u = que[p++]) {
            for (i = 0; i < n; i++) {
                if (!pre[i] && (j = c[u][i])) {
					que[q++] = i;
                    pre[i] = u + 1;
					if (delta > j) delta = j;
				}
			}
		}
        if (!pre[sink]) break;
		flow += delta;
        for (i = sink; i != source; i = pre[i] - 1) {
            c[pre[i] - 1][i] -= delta;
            c[i][pre[i] - 1] += delta;
		}
    }
    return flow;
}

int main()
{
    return 0;
}

