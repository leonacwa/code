/*  转换成图，用单源最短路解决
 * */

#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;
const int NN = 1003;
int r, c;
char mat[NN][NN];
int ma[NN*2][NN*2];
bool vis[NN*2];
int len[NN*2];

void dijkstra(int s, int n)
{
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= n; ++i) {
		len[i] = INT_MAX;
	}
	len[s] = 0;
	for (int i = 0; i < n; ++i) {
		int minLen = INT_MAX, k = -1;
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && minLen > len[j]) {
				minLen = len[j];
				k = j;
			}
		}
		if (k == -1) break;
		vis[k] = true;
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && ma[k][j] != -1 && len[j] > minLen + ma[k][j]) {
				len[j] = minLen + ma[k][j];
			}
		}
	}
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		memset(ma, -1, sizeof(ma));
		scanf("%d %d", &r, &c);
		for (int i = 0; i < r; ++i) {
			scanf("%s", mat[i]);
			for (int j = 0; j < c; ++j) {
				if (mat[i][j] == '#') {
					ma[i][r+j] = 1;
					ma[r+j][i] = 1;
				}
			}
		}
		dijkstra(0, r+c);
		if (len[r-1] == INT_MAX) {
			printf("-1\n");
		} else {
			printf("%d\n", len[r-1]);
		}
	}
	return 0;
}

