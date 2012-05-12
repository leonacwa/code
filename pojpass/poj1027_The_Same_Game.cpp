#include <stdio.h>
#include <string.h>

const int R = 10;
const int C = 15;
const int D[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0}};

char g[R][C+1];
bool vis[R][C];

int dfs(int x, int y)
{
	int ret = 1;
	vis[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int xt = x + D[i][0], yt = y + D[i][1];
		if (0 <= xt && xt < R && 0 <= yt && yt < C && !vis[xt][yt] && g[x][y] == g[xt][yt]) {
			ret += dfs(xt, yt);
		}
	}
	return ret;
}

void dfs2(int x, int y)
{
	char color = g[x][y];
	g[x][y] = ' ';
	for (int i = 0; i < 4; i++) {
		int xt = x + D[i][0], yt = y + D[i][1];
		if (0 <= xt && xt < R && 0 <= yt && yt < C && color == g[xt][yt]) {
			dfs2(xt, yt);
		}
	}
}

int main()
{
	int caseN;
	scanf("%d", &caseN);
	for (int cs = 1; cs <= caseN; cs++) {
		for (int i = 0; i < R; i++) {
			scanf("%s", g[i]);
		}
		printf("Game %d:\n\n", cs);
		int score = 0, cnt = 0, remain = 150;
		while (true) {
			int gx, gy, bs = 0;
			memset(vis, 0, sizeof(vis));
			for (int y = 0; y < C; y++) {
				for (int x = R-1; x >= 0; x--) {
					if (!vis[x][y] && g[x][y] != ' ') {
						int t = dfs(x, y);
						if (bs < t) {
							bs = t;
							gx = x;
							gy = y;
						}
					}
				}
			}
			if (bs < 2) {
				break;
			}
			int t = (bs-2) * (bs-2); 
			score += t;
			remain -= bs;
			printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n", ++cnt, 10-gx, gy+1, bs, g[gx][gy], t);
			dfs2(gx, gy);
			for (int y = 0; y < C; y++) {
				int k = R - 1;
				for (int x = R-1; x >= 0; x--) {
					if (g[x][y] != ' ') {
						if (k != x) {
							g[k][y] = g[x][y];
							g[x][y] = ' ';
						}
						k--;
					}
				}
			}
			int k = 0;
			for (int y = 0; y < C; y++) {
				if (g[R-1][y] != ' ') {
					if (k != y) {
						for (int x = R-1; x >= 0; x--) {
							g[x][k] = g[x][y];
							g[x][y] = ' ';
						}
					}
					k++;
				}
			}
		}
		if (remain == 0) {
			score += 1000;
		}
		printf("Final score: %d, with %d balls remaining.\n", score, remain);
		if (cs < caseN) {
			puts("");
		}
		scanf("\n");
	}
	return 0;
}

