#include <stdio.h>
#include <string.h>

const long long INT64_INF = -1ULL>>1;
const int MAXN = 105;
long long g[MAXN][MAXN];
int N, M, S, T, X;
long long d[MAXN][11];
bool used[MAXN][11];

void dijkstra()
{
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < X; k++) {
			d[i][k] = INT64_INF;
		}
	}
	memset(used, 0, sizeof(used));
	d[S][0] = 0;
	while(true) {
		long long min_d = INT64_INF;
		int u = -1;
		int c = -1;
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < X; k++) {
				if (false == used[j][k] && min_d > d[j][k]) {
					u = j;
					c = k;
					min_d = d[j][k];
				}
			}
		}
		if (u == -1 || used[T][0] == true) {
			break;
		}
		used[u][c] = true;
		int n = (c+1) % X;
		for (int v = 0; v < N; v++) {
			if (false == used[v][n] && g[u][v] < INT64_INF && d[v][n] > min_d + g[u][v]) {
				d[v][n] = min_d + g[u][v];
			}
		}
	}
}

int main()
{
	int nCase;
	scanf("%d", &nCase);
	for (int caseN = 1; caseN <= nCase; caseN++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) {
				g[i][j] = INT64_INF;
			}
		}
		for (int i = 0; i < M; i++) {
			int u, v, w;
			scanf ("%d %d %d", &u, &v, &w);
			if (g[u][v] > w) {
				g[u][v] = w;
			}
		}
		scanf("%d %d %d", &S, &T, &X);
		scanf("\n\n");
		dijkstra();
		if (d[T][0] < INT64_INF) {
			printf("%lld\n", d[T][0]);
		} else {
			printf("No Answer!\n");
		}
	}
	return 0;
}

