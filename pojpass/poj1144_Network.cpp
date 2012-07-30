/* POJ 1144 Network
 * 求割点(关节点)个数 
 * */
#include <cstdio>
#include <cstring>
#include <cstdlib>

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

char buf[2048];

int main()
{
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		memset(mat, 0, sizeof(mat));
		//gets(buf);
		getchar();
		while (1) {
			gets(buf);
			int u, v;
			const char delims[] = " ";
			char *ch = strtok(buf, delims);
			if (ch == NULL || *ch == '0') break;
			u = atoi(ch);
			while (ch = strtok(NULL, delims)) {
				v = atoi(ch);
				mat[u][v] = mat[v][u] = 1;
			}
		}
		// Cut Vertext **
		init_cut();
		cut_dfs(1, -1);
		if (subnet[1] > 0) --subnet[1];
		// *********** end
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (subnet[i] > 0) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
