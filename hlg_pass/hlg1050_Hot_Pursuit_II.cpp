#include <stdio.h>
const int MAXN = 1000+5;
const int INF = 999999999;

int g[MAXN][MAXN];
int dis[MAXN];
int pre[MAXN];
int ord[MAXN];
int ts_dis[MAXN];
int s_dis[MAXN];
int m;

void dijkstra()
{
	bool used[MAXN] = {false};
	for (int i = 0; i < m; i++) {
		dis[i] = INF;
	}
	dis[0] = 0;
	pre[0] = INF;
	for (int i = 0; i < m; i++) {
		int k = -1;
		int min_dis = INF;
		for (int j = 0; j < m; j++) {
			if (false == used[j] && dis[j] < min_dis) {
				k = j;
				min_dis = dis[j];
			}
		}
		if (k == -1) {
			break;
		}
		ord[i] = k;
		used[k] = true;
		for (int j = 0; j < m; j++) {
			if (false == used[j] && min_dis + g[k][j] < dis[j]) {
				dis[j] = min_dis + g[k][j];
				pre[j] = k;
			}
		}
	}
}

void second_dijkstra()
{
	for (int i = 0; i < m; i++) {
		int min_dis = INF;
		for (int j = 0; j < m; j++) {
			if (j != pre[i] && dis[j] + g[j][i] < min_dis) {
				min_dis = dis[j] + g[j][i];
			}
		}
		ts_dis[i] = min_dis;
	}
	s_dis[ord[0]] = ts_dis[ord[0]];	
	for (int i = 1; i < m; i++) {
		if (ts_dis[ord[i]] < s_dis[pre[ord[i]]] + g[pre[ord[i]]][ord[i]]) {
			s_dis[ord[i]] = ts_dis[ord[i]]; 
		} else {
			s_dis[ord[i]] = s_dis[pre[ord[i]]] + g[pre[ord[i]]][ord[i]];
		}
	}
}

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
		dijkstra();
		second_dijkstra();
		printf("%d\n", s_dis[m-1]);
	}
	return 0;
}

