#include <cstdio>
#include <cstring>
#include <climits>

/* 最大流SAP 邻接表
 * GAP + 当前弧优化
 * GAP: 间隙优化
 * 当前弧：是的每次寻找增广路时间变为O(V)
 * */

const int INF = INT_MAX / 3;
const int MAXN = 20000 + 5;
const int MAXM = 200000 + 5;

struct Edge {
	int u, v;
	int c;
	int next;
	Edge() {}
	Edge(int tu, int tv, int tc, int tn) : u(tu), v(tv), c(tc), next(tn) {}
};

Edge E[MAXM * 3];
// head[]顶点弧表表头
int nE, head[MAXN], cnt[MAXN], que[MAXN], d[MAXN], low[MAXN], cur[MAXN];

void addEdge(int u, int v, int c, int rc = 0) { // c 正向弧容量，rc反向弧容量
	E[nE]= Edge(u, v, c, head[u]);
	head[u] = nE++;
	E[nE]= Edge(v, u, rc, head[v]);
	head[v] = nE++;
}

void initNetwork(int n = MAXN) { // head[] 数组初始化为-1
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
	while (d[source] < n) { // que类似于pre数组，存的是边
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

int main()
{
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		initNetwork(n+2);
		for (int i = 1, a, b; i <= n; ++i) {
			scanf("%d%d", &a, &b);
			addEdge(0, i, a, 0);
			addEdge(i, n+1, b, 0);
		}
		for (int i = 0, u, v, w; i < m; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u, v, w, w);
		}
		printf("%d\n", maxflow(n+2, 0, n+1));
	}
	return 0;
}
