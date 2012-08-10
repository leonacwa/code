#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int cdx[4] = {-1, 0, 1, 0}, cdy[4] = {0, 1, 0, -1};
const int mdx[4] = {-1, 0, 1, 0}, mdy[4] = {0, 1, 0, -1};

struct Node {
	int cx, cy, mx, my, px, py;
	Node (int tcx = -1, int tcy = -1, int tmx = -1, int tmy = -1, int tpx = -1, int tpy = -1)
		: cx(tcx), cy(tcy), mx(tmx), my(tmy), px(tpx), py(tpy)
	{}
};
int n, m;
char b[11][11];
int opt[11][11][11][11][11][11];

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d", &n, &m)) {
		int cx, cy, mx, my, px, py;
		for (int i = 0; i < n; ++i) {
			scanf("%s", b[i]);
			for (int j = 0; j < m; ++j) {
				if (b[i][j] == 'C') {
					cx = i, cy = j;
				} else if (b[i][j] == 'M') {
					mx = i, my = j;
				} else if (b[i][j] == 'P') {
					px = i, py = j;
				}
			}
		}
		int ans = -1;
		memset(opt, 0x3f, sizeof(opt));
		opt[cx][cy][mx][my][px][py] = 0;
		queue<Node> Q;
		Q.push(Node(cx, cy, mx, my, px, py));
		while (!Q.empty()) {
			Node tn = Q.front();
			Q.pop();
			cx = tn.cx, cy = tn.cy, mx = tn.mx, my = tn.my, px = tn.px, py = tn.py;
			int now = opt[cx][cy][mx][my][px][py];
			// Chario
			for (int i = 0; i < 4; ++i) {
				int x = tn.cx, y = tn.cy;
				x += cdx[i], y += cdy[i];
				while (0 <= x && x < n && 0 <= y && y < m) {
					if (b[x][y] == 'D' || (x == mx && y == my) || (x == px && y == py)) break;
					if (opt[x][y][mx][my][px][py] == -1 || opt[x][y][mx][my][px][py] > now + 1) {
						opt[x][y][mx][my][px][py] = now + 1;
						if (b[x][y] == 'S') {
							ans = now + 1;
							goto PrintAns;
						}
						Q.push(Node(x, y, mx, my, px, py));
					}
					x += cdx[i], y += cdy[i];
				}
			}
			// Horse  Ma
			for (int i = 0; i < 4; ++i) {
				int x = tn.mx, y = tn.my;
				x += mdx[i], y += mdy[i];
				if (!(0 <= x && x < n && 0 <= y && y < m)) continue;
				if (b[x][y] == 'D' || (x == cx && y == cy) || (x == px && y == py)) continue;
				x += mdx[i], y += mdy[i];
				if (!(0 <= x && x < n && 0 <= y && y < m)) continue;
				int x2 = x, y2 = y;
				for (int j = -1; j <= 1; j += 2) {
					int k = (i + 4 + j) % 4;
					x = x2 + mdx[k], y = y2 + mdy[k];
					if (!(0 <= x && x < n && 0 <= y && y < m)) continue;
					if (b[x][y] == 'D' || (x == cx && y == cy) || (x == px && y == py)) continue;
					if (opt[cx][cy][x][y][px][py] == -1 || opt[cx][cy][x][y][px][py] > now + 1) {
						opt[cx][cy][x][y][px][py] = now + 1;
						if (b[x][y] == 'S') {
							ans = now + 1;
							goto PrintAns;
						}
						Q.push(Node(cx, cy, x, y, px, py));
					}
				}
			}
			// Cannon  Pao
			for (int i = 0; i < 4; ++i) {
				int x = tn.px + cdx[i], y = tn.py + cdy[i];
				while (0 <= x && x < n && 0 <= y && y < m) {
					if (b[x][y] == 'D' || b[x][y] == 'S' || ( x == cx && y == cy) || (x == mx && y == my)) {
						break;
					}
					if (opt[cx][cy][mx][my][x][y] == -1 || opt[cx][cy][mx][my][x][y] > now + 1) {
						opt[cx][cy][mx][my][x][y] = now + 1;
						Q.push(Node(cx, cy, mx, my, x, y));
					}
					x += cdx[i], y += cdy[i];
				}
				if (!(0 <= x && x < n && 0 <= y && y < m)) continue;
				x += cdx[i], y += cdy[i];
				while (0 <= x && x < n && 0 <= y && y < m && b[x][y] != 'D') {
					if (( x == cx && y == cy) || (x == mx && y == my)) break;
					if (b[x][y] == 'S') {
						ans = now + 1;
						goto PrintAns;
					}
					x += cdx[i], y += cdy[i];
				}
			}
		}
PrintAns:
		printf("Scenario #%d\n", ++nCase);
		if (-1 == ans) {
			puts("OH!That's impossible!\n");
		} else {
			printf("%d\n\n", ans);
		}
	}
	return 0;
}

