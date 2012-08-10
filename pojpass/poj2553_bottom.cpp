#include <cstdio>
#include <cstring>

const int MAXN = 5005;
const int MAXM = 5005 * 100; 

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

int oud[MAXN];

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		if (n == 0) break;
		memset(V, 0, sizeof(V));
		nA = 0;
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			addArc(a-1, b-1);
		}
		init_sc_tarjan();
		for (int i = 0; i < n; ++i) {
			if (vis[i] == 0) sc_tarjan(i);
		}
		memset(oud, 0, sizeof(oud));
		for (int i = 0; i < n; ++i) {
			int u = id[i];
			for (Arc *a = V[i]; a; a = a->next) {
				int v = id[a->to];
				if (u != v) {
					++oud[u];
				}
			}
		}
		bool first = true;
		for (int i = 0; i < n; ++i) {
			if (oud[id[i]] == 0) {
				if (first) first = false;
				else putchar(' ');
				printf("%d", i + 1);
			}
		}
		puts("");
	}
}

