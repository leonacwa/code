/* 海岛
 * */
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
	Point() {}
	Point(int tx, int ty) {x = tx, y = ty; }
};

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

int g[105][105];
int hl[105][105];
bool inq[105][105];

int main() {
	char sysInputFile[] = "{sysFileUrl}";
	//freopen(sysInputFile, "r", stdin);
	int n, m, h, s, f, sx, sy, tx, ty;
	while (EOF != scanf("%d%d%d%d%d", &n, &m, &h, &s, &f)) {
		scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &hl[i][j]);
			}
		}
		queue<Point> que;
		memset(g, -1, sizeof(g));
		memset(inq, 0, sizeof(inq));
		g[sx][sy] = 0;
		que.push(Point(sx, sy));
		inq[sx][sy] = true;
		while (!que.empty()) {
			Point pt = que.front();
			que.pop();
			inq[pt.x][pt.y] = false;
			int s_now = g[pt.x][pt.y], h_now = hl[pt.x][pt.y];
			for (int i = 0; i < 4; ++i) {
				int x = pt.x + dx[i], y = pt.y + dy[i];
				if (0 < x && x <= n && 0 < y && y <= m) {
					int t = abs(hl[x][y] - h_now) + f; // land to land
					if (h > h_now && h > hl[x][y]) { // ocean to ocean
						t = min(t, s);
					}
					if (h > h_now && h_now < hl[x][y]) { // ocean to land
						t = min(t, ((h <= hl[x][y]) ? hl[x][y] - h : 0) + f);
					}
					if (h > hl[x][y] && h_now > hl[x][y]) { //  land to ocean
						t = min(t, ((h <= h_now) ? h_now - h : 0) + f);
					}
					t += s_now;
					if (g[x][y] == -1 || g[x][y] > t) {
						g[x][y] = t;
						if (!inq[x][y]) {
							inq[x][y] = true;
							que.push(Point(x, y));
						}
					}
				}
			}
		}
		printf("%d\n", g[tx][ty]);
	}
	return 0;
}
