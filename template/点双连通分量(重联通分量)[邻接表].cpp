/* 点双连通分量(重联通分量)
 * 由无向图割点求法改进而来
 * 邻接表实现
 * 时间复杂度： O(V+E)
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 1005;
const int MAXM = 1000005;

struct Arc {
	int to;
	Arc * next;
	Arc(int tto=0, Arc *tn=NULL) : to(tto), next(tn) {}
} A[MAXM], *V[MAXN];
int nA, depth, vis[MAXN], low[MAXN];
int col[MAXN];
bool mark[MAXN], ok[MAXN];
bool mat[MAXN][MAXN];
int n, m;

struct Edge {
	int u, v;
	Edge(int tu=0, int tv=0) : u(tu), v(tv) {};
} E_stack[MAXM];
int topE;

void addArc(int u, int v) {
	A[nA] = Arc(v, V[u]);
	V[u] = A + nA++;
}

void dfs(int u, int pu) {
	vis[u] = low[u] = ++depth;
	for (Arc *a = V[u]; a; a = a->next) {
		if (pu == a->to) continue;
		int v = a->to;
		if (0 == vis[v]) {
			E_stack[++topE] = Edge(u, v);
			dfs(v, u);
			if (low[u] > low[v]) low[u] = low[v];
			if (low[v] >= vis[u]) { // 割点包含着一个重连通分量
				memset(mark, 0, sizeof(mark));
				while (topE >= 0) {
					Edge e = E_stack[topE--];
					mark[e.u] = mark[e.v] = true; // e<u, v>是一个重连通分量的边
					if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) break;
				}
			}
		} else if (low[u] > vis[v]) low[u] = vis[v];
	}
}

int main()
{
	while (EOF != scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		memset(mat, 0, sizeof(mat));
		memset(V, 0, sizeof(V));
		nA = 0;
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			mat[a][b] = mat[b][a] = true;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = i+1; j <= n; ++j) {
				if (mat[i][j] == false) {
					addArc(i, j);
					addArc(j, i);
				}
			}
		}
		topE = -1;
		memset(vis, 0, sizeof(vis));
		depth = 0;
		for (int i = 1; i <= n; ++i) {
			if (vis[i] == 0) {
				dfs(i, -1);
			}
		}
	}
	return 0;
}
