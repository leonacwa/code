/* POJ 3177 Redundant Paths
 * 边双连通分量, 割边, 缩点
 * */
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 5002;

bool mat[MAXN][MAXN];
vector<int> adj[MAXN];
int depth, vis[MAXN], low[MAXN];
int d[MAXN];
int nBridge, bridge[MAXN][2];

int fa[MAXN];
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) fa[fy] = fx;
}

void dfs(int u, int pu) {
	vis[u] = low[u] = ++depth;
	int size = adj[u].size();
	for (int i = 0, v; i < size; ++i) {
		v = adj[u][i];
		if (v == pu) continue;
		if (0 == vis[v]) {
			dfs(v, u);
			if (low[u] > low[v]) low[u] = low[v];
			if (low[v] > vis[u]) { // 割边， 桥
				bridge[nBridge][0] = u, bridge[nBridge][1] = v;
				++nBridge;
			} else {
				join(u, v);
			}
		} else {
			if (low[u] > vis[v]) low[u] = vis[v];
		}
	}
}

int main()
{
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		for (int i = 0; i <= n; ++i) {
			adj[i].clear();
			fa[i] = i;
			nBridge = 0;
			for (int j = 0; j <= n; ++j) mat[i][j]  = 0;
		}
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			if (mat[a][b]) continue;
			mat[a][b] = mat[b][a] = 1;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		memset(vis, 0, sizeof(vis));
		memset(d, 0, sizeof(d));
		depth = 0;
		dfs(1, -1);
		for (int i = 0; i < nBridge; ++i) {
			int u = bridge[i][0], v = bridge[i][1];
			++d[find(u)], ++d[find(v)];
		}
		int leaf = 0;
		for (int i = 1; i <= n; ++i) {
			if (d[i] == 1) ++leaf;
		}
		printf("%d\n", (leaf + 1) / 2);
	}
	return 0;
}
