#include <cstdio>
#include <cstring>
#include <cstdlib>

/* 求无向图的关节点(割点)
 * Tarjan算法
 * 时间复杂度 O(V+E)
 * */
const int MAXN = 105;

int mat[MAXN][MAXN];
int vis[MAXN], low[MAXN], depth, subnet[MAXN];
int n;

void init_cut() {
	memset(vis, 0, sizeof(vis));
	memset(subnet, 0, sizeof(subnet));
	depth = 0;
}

void cut_dfs(int u, int pu) { // tarjan算法
	vis[u] = low[u] = ++depth;
	for (int v = 1; v <= n; ++v) {
		if (pu != v && mat[u][v]) {
			if (0 == vis[v]){
				cut_dfs(v, u);
				if (low[v] >= vis[u]) ++subnet[u];
				if (low[u] > low[v]) low[u] = low[v];
			} else if (low[u] > vis[v]) low[u] = vis[v];
		}
	}
}

int main()
{
	// 读取数据
	// Cut Vertext **
	init_cut();
	cut_dfs(1, -1);
	if (subnet[1] > 0) --subnet[1]; // 1 是根，如果只有一个孩子则根不是割点
	// *********** end
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (subnet[i] > 0) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}
