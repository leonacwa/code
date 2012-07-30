/* POJ 1523 SPF
 * 无向图求割点
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
	int u, v, n, s, run = 0;
	while (EOF != scanf("%d", &u)) {
		if (0 == u) break;
		++run;
		n = 0, s = MAXN;
		memset(V, 0, sizeof(V));
		nE = 0;
		scanf("%d", &v);
		//printf("%d %d\n", u, v);
		if (n < u) n = u; if (n < v) n = v;if (s > u) s = u; if (s > v) s = v;
		addgEdge(u, v);
		addgEdge(v, u);
		while (EOF != scanf("%d", &u)) {
			if (u == 0) break;
			scanf("%d", &v);
			//printf("%d %d\n", u, v);
			if (n < u) n = u; if (n < v) n = v;if (s > u) s = u; if (s > v) s = v;
			addgEdge(u, v);
			addgEdge(v, u);
		}
		init_cut();
		cut_dfs(s, -1);
		if (subnet[s] > 0) --subnet[s];
		bool find = false;
		printf("Network #%d\n", run);
		for (int i = 1; i <= n; ++i) {
			if (subnet[i] > 0) {
				find = true;
				printf("  SPF node %d leaves %d subnets\n", i, subnet[i] + 1);
			}
		}
		if (false == find) puts("  No SPF nodes");
		scanf("\n");
		puts("");
	}
	return 0;
}
