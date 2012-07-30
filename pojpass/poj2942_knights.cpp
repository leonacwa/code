/* POJ 2942 Knights of the Round Table
 * 重连通分量 + 交叉染色
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

bool color(int u, int pu) {
	for (Arc *a = V[u]; a; a = a->next) {
		if (mark[a->to]) {
			if (col[a->to] == -1) {
				col[a->to] = !col[u];
				return color(a->to, u);
			} else if (col[u] == col[a->to]) {
				return 1;
			}
		}
	}
	return 0;
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
			if (low[v] >= vis[u]) {
				memset(mark, 0, sizeof(mark));
				while (topE >= 0) {
					Edge e = E_stack[topE--];
					mark[e.u] = mark[e.v] = true;
					if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) break;
				}
				memset(col, -1, sizeof(col));
				col[u] = 0;
				if (color(u, -1)) {
					for (int i = 1; i <= n; ++i) {
						if (mark[i]) ok[i] = 1;
					}
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
		memset(ok, 0, sizeof(ok));
		depth = 0;
		for (int i = 1; i <= n; ++i) {
			if (vis[i] == 0) {
				dfs(i, -1);
			}
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (!ok[i]) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
