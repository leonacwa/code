#include <stdio.h>
const int MAXN = 1000+5;
const int INF = 999999999;

int g[MAXN][MAXN];
int dis[MAXN][3];
int v[MAXN];
int m;
int x = 2; 

int main()
{
	while (EOF != scanf("%d", &m)) {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++) {
				g[i][j] = INF;
			}
		}
		for (int i = 0; i < m; i++) {
			int n;
			scanf("%d", &n);
			for (int j = 0; j < n; j++) {
				int a, w;
				scanf("%d %d", &a, &w);
				g[i][a-1] = w;
			}
		}
		for (int i = 0; i < m; i++) {
			v[i] = 0;
			for (int j = 0; j <= x; j++) {
				dis[i][j] = INF;
			}
		}
		dis[0][0] = 0;
		while (true) {
			int min_dis = INF;
			int k = -1;
			for (int i = 0; i < m; i++) {
				if (v[i] < x && dis[i][v[i]] < min_dis) {
					k = i;
					min_dis = dis[i][0];
				}
			}
			if (k == -1 || (k == m-1 && v[m-1] == x-1)) {
				break;
			}
			for (int i = 0; i < m; i++) {
				if (v[i] < x && dis[k][v[k]] + g[k][i] < dis[i][x]) {
					dis[i][x] = dis[k][v[k]] + g[k][i];
					for (int j = x; j > 0; j--) {
						if (dis[i][j] < dis[i][j-1]) {
							int t = dis[i][j];
							dis[i][j] = dis[i][j-1];
							dis[i][j-1] = t;
						}
					}
				}
			}
			v[k]++;
		}
		printf("%d\n", dis[m-1][x-1]);
	}
	return 0;
}
