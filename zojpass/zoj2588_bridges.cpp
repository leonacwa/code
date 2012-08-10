/*ZOJ 2588 Burning Bridges
 * 无向图的割边
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 10005;
const int MAXM = 200005;

struct Edge {
	int to;
	Edge *next;
	int id, tag;
	Edge() {}
	Edge(int tto, Edge* tn, int ti, int tt) : to(tto), next(tn), id(ti), tag(tt) {}
} E[MAXM], *V[MAXN];
int nE;
int depth, vis[MAXN], low[MAXN];
int nBridges, bridge[MAXM];

void addEdge(int u, int v, int id) {
	for (Edge *e = V[u]; e; e = e->next) {
		if (e->to == v) {
			e->tag++;
			return;
		}
	}
	E[nE] = Edge(v, V[u], id, 0);
	V[u] = E + nE++;
}

void dfs(int u, int pu) {
	vis[u] = low[u] = ++depth;
	for (Edge *e = V[u]; e; e = e->next) {
		if (e->to == pu) continue;
		int v = e->to;
		if (0 == vis[v]) {
			dfs(v, u);
			if (low[u] > low[v]) low[u] = low[v];
			if (low[v] > vis[u] && e->tag == 0) { // 割边
				bridge[e->id] = ++nBridges;
			}
		} else {
			if (low[u] > vis[v]) low[u] = vis[v];
		}
	}
}

int main()
{
	int runs, n, m;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d%d", &n, &m);
		nE = 0;
		memset(V, 0, sizeof(V));
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			addEdge(a, b, i);
			addEdge(b, a, i);
			bridge[i] = 0;
		}
		memset(vis, 0, sizeof(vis));
		nBridges = 0;
		depth = 0;
		dfs(1, -1);
		printf("%d\n", nBridges);
		bool first = true;
		for (int i = 0; i < m; ++i) {
			if (bridge[i]) {
				if (first) first = false;
				else putchar(' ');
				printf("%d", i + 1);
			}
		}
		if (!first) puts("");
		if (runs) puts("");
	}
	return 0;
}
