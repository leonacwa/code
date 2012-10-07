/* 最小费用流
 * 邻接表 + SPFA + Dinic
 * 时间复杂度：O(V*E*f)
 * 比赛的时候建议封装成一个结构体进行使用
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
	/* SPFA，根据需要使用cnt[]数组统计顶点入队次数，入队次数>=n则表示存在负权环，
	 * 也可以使用dfs深搜，如果遇到已经出现的点说明存在负权环
	 * 实际中SPFA算法的效率不稳定，可以使用更加稳定的Dijkstra算法
	 * */

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


int main()
{
	int n, k, nn, source, sink;
	while (EOF != scanf("%d%d", &n, &k)) {
		nn = n * n;
		source = 2 * nn;
		sink = 2 * nn + 1;
		net.init();
		for (int i = 0; i < n; ++i) {
			for (int j = 0, d, u, v; j < n; ++j) {
				scanf("%d", &d);
				u = i * n + j;
				net.addEdge(u, nn + u, 1, -d);
				if (i+1 < n) {
					v = (i + 1) * n + j;
					net.addEdge(u, v, INF, 0);
					net.addEdge(nn+u, v, INF, 0);
					net.addEdge(nn+u, nn+v, INF, 0);
				}
				if (j+1 < n) {
					v = i * n + j + 1;
					net.addEdge(u, v, INF, 0);
					net.addEdge(nn+u, v, INF, 0);
					net.addEdge(nn+u, nn+v, INF, 0);
				}
			}
		}
		net.addEdge(source, 0, k,  0);
		net.addEdge(2*nn - 1, sink, k,  0);
		printf("%d\n", -net.mincost_maxflow(2*nn + 2, source, sink));
	}
	return 0;
}
