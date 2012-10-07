/* 无向图求割点
 * 邻接表
 * Tarjan算法
 * 时间复杂度:O(V+E)
 * */
#include <cstdio>
#include <cstring>
const int MAXN = 1005;
struct Edge {
	int to;
	Edge * next;
	Edge(int tto=0, Edge *tn=NULL) : to(tto), next(tn) {}
} E[MAXN * MAXN], *V[MAXN];
int nE;

int vis[MAXN], low[MAXN], depth, subnet[MAXN];

void addgEdge(int u, int v) {
	E[nE] = Edge(v, V[u]);
	V[u] = E + nE++;
}

void init_cut() {
	depth = 0;
	memset(subnet, 0, sizeof(subnet));
	memset(vis, 0, sizeof(vis));
}

void cut_dfs(int u, int pu) {
	vis[u] = low[u] = ++depth;
	for (Edge *e = V[u]; e; e = e->next) {
		if (pu == e->to) continue;
		int v = e->to;
		if (0 == vis[v]) {
			cut_dfs(v, u);
			if (low[u] > low[v]) low[u] = low[v];
			if (low[v] >= vis[u]) ++subnet[u];
		} else if (low[u] > vis[v]) low[u] = vis[v];
	}
}

int main()
{
	/// 读入数据
	init_cut();
	cut_dfs(1, -1);
	if (subnet[1] > 0) --subnet[1];
	return 0;
}
