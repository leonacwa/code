#include <stdio.h>
#include <string.h>

const int MAXN = 1000+1;
const int INF = 999999999;
int g[MAXN][MAXN], gr[MAXN][MAXN];
int d[MAXN], dr[MAXN];
bool vis[MAXN];
int N, M, X;

void dijkstra(int g[MAXN][MAXN], int d[MAXN])
{
	for (int i = 0; i <= N; i++) {
		d[i] = INF;
		vis[i] = false;
	}
	d[X] = 0;
	for (int i = 0; i < N; i++) {
		int min_d = INF;
		int k = -1;
		for (int j = 1; j <= N; j++) {
			if (false == vis[j] && min_d > d[j]) {
				min_d = d[j];;
				k = j;
			}
		}
		if (k == -1) {
			break;
		}
		vis[k] = true;
		for (int j = 1; j <= N; j++) {
			if (false == vis[j] && d[j] > d[k] + g[k][j]) {
				d[j] = d[k] + g[k][j];
			}
		} 
	}
}

int main()
{
	while (EOF != scanf("%d %d %d", &N, &M, &X)) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				g[i][j] = INF;
				gr[i][j] = INF;
			}
		}
		for (int i = 0; i < M; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			if (g[u][v] > w) {
				g[u][v] = w;
				gr[v][u] = w;
			}
		}
		dijkstra(g, d);
		dijkstra(gr, dr);
		int max_d = 0;
		for (int i = 1; i <= N; i++) {
			if (max_d < d[i] + dr[i]) {
				max_d = d[i]+ dr[i];
			}
		}
		printf("%d\n", max_d);
	}
	return 0;
}
