#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

const int NN = 101;
int mat[NN][NN];
int A, B, K, L;

void floyd()
{
	int n = A + B;
	for (int k = 0; k < A; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (mat[i][k] != -1 && mat[k][j] != -1) {
					if (mat[i][j] == -1) {
						mat[i][j] = mat[i][k] + mat[k][j];
					} else {
						mat[i][j] = min(mat[i][k] + mat[k][j], mat[i][j]);
					}
				}
			}
		}
	}
}

int f[NN][11];
bool vis[NN][11];

int dijkstra()
{
	int n = A + B;
	floyd();
	memset(f, -1, sizeof(f));
	memset(vis, 0, sizeof(vis));
	f[n-1][0] = 0;
	for (int cnt = 0; cnt < (1+K)*n; ++cnt) {
		int minDis = INT_MAX;
		int ci, ck;
		for (int ik = 0; ik <= K; ++ik) {
			for (int i = 0; i < n; ++i) {
				if (!vis[i][ik] && f[i][ik] != -1 && f[i][ik] < minDis) {
					minDis = f[i][ik];
					ci = i;
					ck = ik;
				}
			}
		}
		if (minDis == INT_MAX) break;
		//printf("minDis:%d\n", minDis);
		vis[ci][ck] = true;
		for (int i = 0; i < n; ++i) {
			if (mat[ci][i] != -1) {
				if (!vis[i][ck] && (f[i][ck] == -1 || f[i][ck] > f[ci][ck] + mat[ci][i])) {
					f[i][ck] = f[ci][ck] + mat[ci][i];
				}
				if (ck < K && !vis[i][ck+1] && mat[ci][i] <= L && (f[i][ck+1] == -1 || f[i][ck+1] > f[ci][ck])) {
					f[i][ck+1] = f[ci][ck];
				}
			}
		}
	}
	int ans = INT_MAX;
	for (int i = 0; i <= K; ++i) {
		if (f[0][i] != -1 && ans > f[0][i]) {
			ans = f[0][i];
		}
	}
	return ans;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int m;
		scanf("%d %d %d %d %d", &A, &B, &m, &L, &K);
		memset(mat, -1, sizeof(mat));
		for (int i = 0; i < m; ++i) {
			int x, y, l;
			scanf("%d %d %d", &x, &y, &l);
			x--, y--;
			mat[x][y] = mat[y][x] = l;
		}
		printf("%d\n", dijkstra());
	}
	return 0;
}