/* POJ 1236 Network of Schools
 * */
#include <cstdio>
#include <cstring>
const int MAXN = 105;
const int MAXM = 10005;

struct Arc {
	int to;
	Arc * next;
	Arc() {}
	Arc(int tto, Arc *tn) : to(tto), next(tn) {}
};
int nA;
Arc A[MAXM], *V[MAXN];
int order, vis[MAXN], low[MAXN];
int sc_cnt, top, vstack[MAXN], id[MAXN];
bool instack[MAXN];

void addArc(int u, int v) {
	A[nA] = Arc(v, V[u]);
	V[u] = A + nA++;
}

void init_sc_tarjan() {
	memset(vis, 0, sizeof(vis));
	memset(instack, 0, sizeof(instack));
	top = -1;
	order = 0;
	sc_cnt = 0;
}

void sc_tarjan(int u) {
	vis[u] = low[u] = ++order;
	instack[u] = true;
	vstack[++top] = u;
	int v;
	for (Arc *a = V[u]; a; a = a->next) {
		v = a->to;
		if (vis[v] == 0) {
			sc_tarjan(v);
			if (low[u] > low[v]) low[u] = low[v];
		} else if (instack[v] && low[u] > vis[v]) {
			low[u] = vis[v];
		}
	}
	if (vis[u] == low[u]) {
		do {
			v = vstack[top--];
			instack[v] = false;
			id[v] = sc_cnt; // 顶点v所在连通分量的集合
		} while (u != v);
		sc_cnt++;
	}
}

int ind[MAXN], oud[MAXN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		memset(V, 0, sizeof(V));
		nA = 0;
		for (int i = 1, v; i <= n; ++i) {
			while (EOF != scanf("%d", &v)) {
				if (v == 0) break;
				addArc(i, v);
			}
		}
		init_sc_tarjan();
		for (int i = 1; i <= n; ++i) {
			if (vis[i] == 0) sc_tarjan(i);
		}
		memset(ind, 0, sizeof(ind));
		memset(oud, 0, sizeof(oud));
		for (int i = 1; i <= n; ++i) {
			int u = id[i];
			for (Arc *a = V[i]; a; a= a->next) {
				int v = id[a->to];
				if (u != v) {
					++oud[u], ++ind[v];
				}
			}
		}
		int ans1 = 0, ans2 = 0;
		for (int i = 0; i < sc_cnt; ++i) {
			if (ind[i] == 0) ++ans1;
			if (oud[i] == 0) ++ans2;
		}
		if (ans2 < ans1) ans2 = ans1;
		if (sc_cnt == 1) ans2 = 0;
		printf("%d\n%d\n", ans1, ans2);
	}
}
