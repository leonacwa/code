/* HDU 4435	 charge-station
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 129;
const int INF = 99999999;
int n, d;
int x[MAXN], y[MAXN];
int mat[MAXN][MAXN];
int dis[MAXN];
bool inq[MAXN];
bool oil[MAXN];

bool bfs() {
	for (int i = 0; i < n; ++i) dis[i] = INF;
	dis[0] = 0;
	queue<int> que;
	memset(inq, 0, sizeof(inq));
	inq[0] = 1;
	que.push(0);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		inq[u] = 0;
		for (int i = 0; i < n; ++i) {
			int t = dis[u] + mat[u][i];
			if (mat[u][i] <= d && dis[i] > t) {
				dis[i] = t;
				if (!inq[i] && oil[i]) {
					que.push(i);
					inq[i] = 1;
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) if (dis[i] == INF) return false;
	for (int i = 0; i < n; ++i) {
		if (!oil[i]) {
			int mm = INF;
			for (int j = 0; j < n; ++j) {
				if (oil[j] && mat[i][j] < mm) {
					mm = mat[i][j];
				}
			}
			if (mm * 2 > d) return false;
		}
	}
	return true;
}

int main() {
	while (EOF != scanf("%d%d", &n, &d)) {
		for (int i = 0; i < n; ++i)  {
			scanf("%d%d", &x[i], &y[i]);
		}
		for (int i = 0; i < n; ++i) {
			mat[i][i] = 0;
			for (int j = i + 1; j < n; ++j) {
				mat[i][j] = mat[j][i] = (int)ceil(sqrt( (double)(x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) ));
			}
		}
		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (mat[i][j] > mat[i][k] + mat[k][j]) mat[i][j] = mat[i][k] + mat[k][j];
				}
			}
		}
		memset(oil, 1, sizeof(oil));
		if (!bfs()) {
			puts("-1");
		} else {
			for (int i = n-1; i > 0; --i) {
				oil[i] = 0;
				if (!bfs()) oil[i] = 1;
			}
			int i = n - 1;
			while (!oil[i]) --i;
			for (; i >= 0; --i) putchar(oil[i] ? '1' : '0');
			puts("");
		}
	}
	return 0;
}
