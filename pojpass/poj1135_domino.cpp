#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;
const int NN = 501;
int n, m;
int mat[NN][NN];
int len[NN];
bool vis[NN];

void dijkstra(int s)
{
	memset(len, -1, sizeof(len));
	memset(vis, 0, sizeof(vis));
	len[s] = 0;
	for (int i = 0; i < n; ++i) {
		int minLen = INT_MAX;
		int u = -1;
		for (int j = 1; j <= n; ++j) {
			if (!vis[j] && len[j] != -1 && minLen > len[j]) {
				minLen = len[j];
				u = j;
			}
		}
		if (u == -1) return;
		vis[u] = true;
		for (int j = 1; j <= n; ++j) {
			if (!vis[j] && mat[u][j] != -1 && (len[j] == -1 || len[j] > minLen + mat[u][j])) {
				len[j] = minLen + mat[u][j];
			}
		}
	}
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d", &n, &m)) {
		if (n == 0 && m == 0) break;
		memset(mat, -1, sizeof(mat));
		for (int i = 0; i < m; ++i) {
			int a, b, t;
			scanf("%d %d %d", &a, &b, &t);
			mat[a][b] = mat[b][a] = t;
		}
		int u, v, k;
		dijkstra(1);
		double max1 = -INT_MAX, max2 = -INT_MAX;
		for (int i = 1; i <= n; ++i) {
			if (max1 < len[i]) {
				max1 = len[i];
				k = i;
			}
			for (int j = i + 1; j <= n; ++j) {
				if (mat[i][j] != -1 && max2 < len[i] + len[j] + mat[i][j]) {
					max2 = len[i] + len[j] + mat[i][j];
					u = i;
					v = j;
				}
			}
		}
		max2 /= 2;
		printf("System #%d\n", ++nCase);
		if (max2 > max1 + 1e-6) {
			printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n", max2, u, v);
		} else {
			printf("The last domino falls after %.1f seconds, at key domino %d.\n", max1, k);
		}
		puts("");
	}
	return 0;
}

