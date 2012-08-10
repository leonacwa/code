/* Escape from Enemy Territory
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

struct Point {
	int x, y;
	Point() {}
	Point(int tx, int ty) : x(tx), y(ty) {}
};

bool mat[MAXN][MAXN];
int stp[MAXN][MAXN];
Point pt[1000005];
int n, X, Y, sx, sy, ex, ey;
Point que[MAXN*MAXN];

int check(int dis) {
	memset(mat, 0, sizeof(mat));
	for (int i = 0; i < n; ++i) {
		for (int dx = 0; dx < dis; ++dx) {
			int x, y, dy = dis - dx - 1;
			x = pt[i].x + dx, y = pt[i].y + dy;
			if (x < 0) x = 0; else if (x >= X) x = X - 1;
			if (y < 0) y = 0; else if (y >= Y) y = Y - 1;
			if (!mat[x][y]) mat[x][y] = true;
			x = pt[i].x + dx, y = pt[i].y - dy;
			if (x < 0) x = 0; else if (x >= X) x = X - 1;
			if (y < 0) y = 0; else if (y >= Y) y = Y - 1;
			if (!mat[x][y]) mat[x][y] = true;
			x = pt[i].x - dx, y = pt[i].y + dy;
			if (x < 0) x = 0; else if (x >= X) x = X - 1;
			if (y < 0) y = 0; else if (y >= Y) y = Y - 1;
			if (!mat[x][y]) mat[x][y] = true;
			x = pt[i].x - dx, y = pt[i].y - dy;
			if (x < 0) x = 0; else if (x >= X) x = X - 1;
			if (y < 0) y = 0; else if (y >= Y) y = Y - 1;
			if (!mat[x][y]) mat[x][y] = true;
		}
	}
	memset(stp, -1, sizeof(stp));
	int fr = 0, ta = 0;
	stp[sx][sy] = 0;
	que[ta++] = Point(sx, sy);
	while (fr < ta) {
		Point p = que[fr++];
		int t = stp[p.x][p.y] + 1;
		for (int i = 0; i < 4; ++i) {
			int x = p.x + dx[i], y = p.y + dy[i];
			if (x < 0 || x >= X || y < 0 || y >= Y) continue;
			if (mat[x][y] || stp[x][y] != -1) continue;
			stp[x][y] = t;
			if (x == ex && y == ey) {
				return t;
			}
			que[ta++] = Point(x, y);
		}
	}
	return -1;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int l = 0, r = 1000000, ans = -1;
		scanf("%d%d%d", &n, &X, &Y);
		scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
		for (int i = 0, t; i < n; ++i) {
			scanf("%d%d", &pt[i].x, &pt[i].y);
			t = abs(pt[i].x - sx) + abs(pt[i].y - sy);
			if (r > t) r = t;
			t = abs(pt[i].x - ex) + abs(pt[i].y - ey);
			if (r > t) r = t;
		}
		while (l < r) {
			int m = (l + r) / 2 + 1;
			int ret = check(m);
			if (ret == -1) {
				r = m - 1;
			} else {
				l = m;
				ans = ret;
			}
		}
		if (ans == -1) ans = check(l);
		printf("%d %d\n", l, ans);
	}
	return 0;
}
