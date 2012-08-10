/* POJ 2762 Going from u to v or from v to u?
 * 强连通分量 + 拓扑排序应用
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 1005;
const int MAXM = 12005;

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

void init_tarjan() {
	memset(vis, 0, sizeof(vis));
	memset(instack, 0, sizeof(instack));
	top = -1;
	order = 0;
	sc_cnt = 0;
}

void tarjan(int u) {
	vis[u] = low[u] = ++order;
	instack[u] = true;
	vstack[++top] = u;
	int v;
	for (Arc *a = V[u]; a; a = a->next) {
		v = a->to;
		if (vis[v] == 0) {
			tarjan(v);
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

bool mat[MAXN][MAXN];
int ord[MAXN], ind[MAXN];

int main()
{
	int runs, n, m;
	scanf("%d", &runs);
	while (runs--) {
		nA = 0;
		memset(V, 0, sizeof(V));
		scanf("%d%d", &n, &m);
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			addArc(a, b);
		}
		init_tarjan();
		for (int i = 1; i <= n; ++i) {
			if (vis[i] == 0) {
				tarjan(i);
			}
		}
		memset(mat, 0, sizeof(mat));
		memset(ind, 0, sizeof(ind));
		for (int i = 1; i <= n; ++i) {
			for (Arc *a = V[i]; a; a = a->next) {
				int u = id[i], v = id[a->to];
				if (u != v && false == mat[u][v]) {
					mat[u][v] = true;
					++ind[v];
				}
			}
		}
		// top sort
		top = -1;
		for (int i = 0; i < sc_cnt; ++i) {
			if (ind[i] == 0) vstack[++top] = i;
		}
		int cnt = 0;
		while (cnt < sc_cnt) {
			int u = vstack[top--];
			ord[cnt++] = u;
			for (int v = 0; v < sc_cnt; ++v) {
				if (mat[u][v]) {
					--ind[v];
					if (ind[v] == 0) vstack[++top] = v;
				}
			}
		}
		bool ans = true;
		for (int i = 0; i < cnt-1; ++i) {
			if (false == mat[ord[i]][ord[i+1]]) {
				ans = false;
				break;
			}
		}
		puts(ans ? "Yes" : "No");
	}
	return 0;
}
