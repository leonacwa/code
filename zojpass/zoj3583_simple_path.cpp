#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int NN = 100 + 5;

bool g[NN][NN];
bool vis[NN];
bool can[NN];
int ans;
int n, m, s, d;

bool dfs(int u) // 暴搜
{
	if (can[u]) {
		return true;
	}
	bool ret = false;
	for (int i = 0; i < n; ++i) {
		if (g[u][i] && !vis[i]) {
			vis[i] = true;
			if (dfs(i)) {
				can[u] = true;
				ret = true;
			}
			vis[i] = false;
		}
	}
	return ret;
}

int main()
{
	while (EOF != scanf("%d %d %d %d", &n, &m, &s, &d)) {
		memset(g, 0, sizeof(g));
		int u, v;
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &u, &v);
			g[u][v] = g[v][u] = true;
		}
		memset(vis, 0, sizeof(vis));
		memset(can, 0, sizeof(can));
		vis[s] = true;
		can[d] = true;
		dfs(s);
		ans = 0;
		for (int i = 0; i < n; ++i) {
			if (can[i] == false) {
		   	   ++ans;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

