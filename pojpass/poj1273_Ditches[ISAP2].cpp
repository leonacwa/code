#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

const int MAXN = 205;
const int MAXM = MAXN * MAXN;
const int INF = INT_MAX / 2;
/* 最大流SAP 邻接表
 * GAP + 当前弧优化
 * GAP:
 * 当前弧：是的每次寻找增广路时间变为O(V)
 * */

struct Edge {
	int u, v;
	int c;
	int next;
	Edge(int tu=0, int tv=0, int tc=0, int tn=0) : u(tu), v(tv), c(tc), next(tn) {}
};

Edge E[MAXM * 3];
int nE, head[MAXN], cnt[MAXN], que[MAXN], d[MAXN], low[MAXN], cur[MAXN];

void addEdge(int u, int v, int c, int rc = 0) { // c 正向弧容量，rc反向弧容量
	E[nE]= Edge(u, v, c, head[u]);
	head[u] = nE++;
	E[nE]= Edge(v, u, rc, head[v]);
	head[v] = nE++;
}

void initNetwork(int n = -1) { // head[] 数组初始化为-1
	if (n == -1) n = MAXN;
	memset(head, -1, sizeof(head[0])*MAXN);
	nE = 0;
}

int maxflow(int n, int source, int sink) {
	int *fr = que, *ta = que;;
	for (int i = 0; i < n; ++i) d[i] = n, cnt[i] = 0;
	cnt[n] = n - 1, cnt[0]++, d[sink] = 0;
	*ta++ = sink;
	while (fr < ta) {
		int v = *fr++;
		for (int i = head[v]; i != -1; i = E[i].next) {
			if (d[E[i].v] == n && E[i^1].c > 0) {
				d[E[i].v] = d[v] + 1;
				cnt[n]--;
				cnt[d[E[i].v]]++;
				*ta++ = E[i].v;
			}
		}
	}
	int flow = 0, u = source, top = 0;
	low[0] = INF;
	for (int i = 0; i < n; ++i) cur[i] = head[i];
	while (d[source] < n) {
		int &i = cur[u];
		for (; i != -1; i = E[i].next) {
			if (E[i].c > 0 && d[u] == d[E[i].v] + 1) {
				low[top+1] = low[top] < E[i].c ? low[top] : E[i].c;
				que[top+1] = i;
				++top;
				u = E[i].v;
				break;
			}
		}
		if (i != -1) {
			if (u == sink) {
				int delta = low[top];
				for (int p = 1, i; p <= top; ++p) {
					i = que[p];
					E[i].c -= delta;
					E[i^1].c += delta;
				}
				flow += delta;
				u = source;
				low[0] = INF;
				top = 0;
			}
		} else {
			int old_du = d[u];
			cnt[old_du]--;
			d[u] = n - 1;
			for (int i = head[u]; i != -1; i = E[i].next) {
				if (E[i].c > 0 && d[u] > d[E[i].v]) d[u] = d[E[i].v];
			}
			cnt[++d[u]]++;
			if (d[u] < n) cur[u] = head[u];
			if (u != source) {
				u = E[que[top]].u;
				--top;
			}
			if (cnt[old_du] == 0) break;
		}
	}
	return flow;
}

int c[MAXN][MAXN];

int main()
{
    int m, n;
    while (EOF != scanf("%d%d", &m, &n)) {
		initNetwork();
		memset(c, 0, sizeof(c));
        for (int i = 0; i < m; ++i) {
            int a, b, f;
            scanf("%d%d%d", &a, &b, &f);
            c[a-1][b-1] += f;
        }
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (c[i][j] > 0) addEdge(i, j, c[i][j]);
			}
		}
        int ans = maxflow(n, 0, n - 1);
		while (ans < 0) ;
        printf("%d\n", ans);
    }
    return 0;
}

