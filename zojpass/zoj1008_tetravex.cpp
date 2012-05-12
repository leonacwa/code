#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n, nn;
int mat[5][5];
int g[25][4];
bool used[25];

bool dfs(int x, int y)
{
	if (x == n) return true;
	int cnt = 0, du[nn][4];
	for (int i = 0; i < nn; ++i) {
		if (used[i]) continue;
		if (x > 0 && g[mat[x-1][y]][2] != g[i][0]) continue;
		if (y > 0 && g[mat[x][y-1]][1] != g[i][3]) continue;
		bool dup = false;
		for (int j = 0; j < cnt; ++j) {
			if (g[i][0] == du[j][0] && g[i][1] == du[j][1] && g[i][2] == du[j][2] && g[i][3] == du[j][3]) {
				dup = true;
				break;
			}
		}
		if (dup) continue;
		du[cnt][0] = g[i][0];
		du[cnt][1] = g[i][1];
		du[cnt][2] = g[i][2];
		du[cnt][3] = g[i][3];
		++cnt;
		used[i] = true;
		mat[x][y] = i;
		if (dfs(x + (y+1) / n, (y+1) % n)) {
			return true;
		}
		used[i] = false;
	}
	return false;
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d", &n) && n > 0) {
		memset(g, 0, sizeof(g));
		nn = n * n;
		for (int i = 0; i < nn; ++i) {
			scanf("%d %d %d %d", &g[i][0], &g[i][1], &g[i][2], &g[i][3]);
		}
		memset(used, 0, sizeof(used));
		bool can = dfs(0, 0);
		if (nCase) puts("");
		printf("Game %d: %s\n", ++nCase, can ? "Possible" : "Impossible");
	}
	return 0;
}

