/* HDU4411 Arrest
 * 本质是有上下界的最小费用最大流，但是因为题目的特殊性，可以变成最小费用最大流。
 * 拆点，必须经过的拆为两点，流量为1，费用为一个很小的负数，这样在选择路径的时候，就一定会选择这些必须经过的点。
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 205, MAXM = MAXN * MAXN + 4*MAXN;
const int INF = 10000007;

struct Network {
	struct Edge {
		int to;
		int c, w;
		int next;
		Edge(int tto=0, int tc=0, int tw=0, int tn=-1) : to(tto), c(tc), w(tw), next(tn) {}
	};
	int nE, V[MAXN]; // nE 边数，V[]顶点的边链表头，顶点初始化为-1, nE初始化为0
	Edge E[MAXM];

	int pre[MAXN];
	int path[MAXN];
	int sp[MAXN]; // 源点到各个点的费用
	int que[MAXN]; 
	bool inq[MAXN];

	void init(int n = MAXN) {
		memset(V, -1, sizeof(V[0]) * n);
		nE = 0;
	}
	void addEdge(int u, int v, int c, int w, int rc = 0) { // rc是反向弧的容量
		E[nE] = Edge(v, c, w, V[u]);
		V[u] = nE++;
		E[nE] = Edge(u, rc, -w, V[v]);
		V[v] = nE++;
	}
	bool SPFA(int n, int source, int sink) {
		int *fr = que, *ta = que; /* 注意fr和ta要一直指向正确的内存位置 */
		for (int i = 0; i < n; ++i) sp[i] = INF, inq[i] = false;
		pre[source] = -1;
		sp[source] = 0;
		*ta++ = source;
		inq[source] = true;
		while (fr != ta) {
			int u = *fr++;
			if (fr == que + MAXN) fr = que;
			inq[u] = false;
			for (int i = V[u], v; i != -1; i = E[i].next) {
				while (i > nE || i < 0) ;
				v = E[i].to;
				if (E[i].c > 0 && sp[v] > sp[u] + E[i].w) {
					sp[v] = sp[u] + E[i].w;
					pre[v] = u;
					path[v] = i;
					if (false == inq[v]) {
						/* SLF Smal Label First 距离更短的顶点在队列前，此优化效果非常明显，推荐使用
						 * 也可以使用 LLL, Large Label Last 进行优化
						 * */
						if (fr != ta && sp[*fr] > sp[v]) {
							fr--;
							if (fr < que) fr = que + MAXN - 1;
							*fr = v;
						} else {
							*ta++ = v;
							if (ta >= que + MAXN) ta = que;
						}
						inq[v] = true;
					}
				}
			}
		}
		return sp[sink] < INF;
	}

	int argument(int n, int source, int sink) {
		int delta = INF;
		for (int i = sink, e; pre[i] != -1; i = pre[i]) {
			e = path[i];
			if (delta > E[e].c) delta = E[e].c;
		}
		for (int i = sink, e; pre[i] != -1; i = pre[i]) {
			e = path[i];
			E[e].c -= delta;
			E[e^1].c += delta;
		}
		return delta;
	}
	// 最小费用最大流
	// 返回最大流的最小费用
	int mincost_maxflow(int n, int source, int sink) {
		int cost = 0; // 费用流 = 费用x流
		while ( SPFA(n, source, sink) ) {
			int delta = argument(n, source, sink); /* delta为每次增广增加的流量 */
			cost += delta * sp[sink];
		}
		return cost;
	}
};
Network net;
int g[105][105];

int main() {
	int n, m, kk;
	while (EOF != scanf("%d%d%d", &n, &m, &kk) && n+m+kk) {
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= n; ++j) g[i][j] = INF;
			g[i][i] = 0;
		}
		for (int i = 0; i < m; ++i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			g[a][b] = g[b][a] = min(g[a][b], c);
		}
		for (int k = 0; k <= n; ++k) {
			for (int i = 0; i <= n; ++i) {
				for (int j = 0; j <= n; ++j) {
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
				}
			}
		}
		net.init();
		int source = n*2+1, sink = n*2+2;
		net.addEdge(source, 0, kk, 0);
		net.addEdge(0, sink, kk, 0);
		for (int i = 1; i <= n; ++i) {
			net.addEdge(i, i+n, 1, -INF);
			net.addEdge(0, i, 1, g[0][i]);
			net.addEdge(i+n, sink, 1, g[0][i]);
			for (int j = i+1; j <= n; ++j) {
				if (g[i][j] < INF) net.addEdge(i+n, j, 1, g[i][j]);
			}
		}
		int ans = net.mincost_maxflow(n*2+3, source, sink) + n*INF;
		printf("%d\n", ans);
	}
	return 0;
}
