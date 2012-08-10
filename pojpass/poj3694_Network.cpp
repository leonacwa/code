/* POJ 3294 Network
 * 双连通分量 + LCA应用
 * */

#include <cstdio>
#include <cstring>

const int MAXN = 100005;
const int MAXM = 400005;

struct Arc {
	int to;
	Arc *next;
	Arc() {}
	Arc(int tto, Arc *tn) : to(tto), next(tn) {}
} A[MAXM], *V[MAXN];
int nA;
int depth, order, vis[MAXN], low[MAXN], lev[MAXN], pre[MAXN];
int nBridge;
bool isBridge[MAXN];

void addArc(int u, int v) {
	for (Arc *a = V[u]; a; a = a->next) {
		if (a->to == v) return;
	}
	A[nA] = Arc(v, V[u]);
	V[u] = A + nA++;
}

void dfs(int u, int pu, int depth) {
	lev[u] = depth;
	vis[u] = low[u] = ++order;
	for (Arc *a = V[u]; a; a = a->next) {
		if (a->to == pu) continue;
		int v = a->to;
		if (vis[v] == 0) {
			pre[v] = u;
			dfs(v, u, depth + 1);
			if (low[u] > low[v]) low[u] = low[v];
			if (low[v] > vis[u]) {
				++nBridge;
				isBridge[v] = 1;
			}
		} else {
			if (low[u] > vis[v]) low[u] = vis[v];
		}
	}
}

void lca(int u, int v) { // lev[u] <= lev[v]
	if (lev[u] > lev[v]) {
		int t = u; u = v; v = t;
	}
	while (lev[u] < lev[v]) {
		if (isBridge[v]) {
			isBridge[v] = 0;
			--nBridge;
		}
		v = pre[v];
	}
	while (u != v) {
		if (isBridge[u]) {
			isBridge[u] = 0;
			--nBridge;
		}
		if (isBridge[v]) {
			isBridge[v] = 0;
			--nBridge;
		}
		u = pre[u], v = pre[v];
	}
}

int main()
{
	int n, m, q, run = 0;
	while (EOF != scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		++run;
		nA = 0;
		memset(V, 0, sizeof(V));
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			addArc(a, b);
			addArc(b, a);
		}
		order = 0;
		nBridge = 0;
		memset(isBridge, 0, sizeof(isBridge));
		memset(vis, 0, sizeof(vis));
		dfs(1, -1, 0);
		scanf("%d", &q);
		printf("Case %d:\n", run);
		for (int i = 0, a, b; i < q; ++i) {
			scanf("%d%d", &a, &b);
			lca(a, b);
			printf("%d\n", nBridge);
		}
		puts("");
	}
	return 0;
}
