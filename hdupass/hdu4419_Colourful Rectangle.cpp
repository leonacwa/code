/* HDU 4419 Colourful Rectangle
 * 矩形切割
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long int64;

const int fx[7] = {1, 2, 4, 3, 5, 6, 7};

struct Rect {
	int x1, y1, x2, y2;
	int c;
};

bool cmp(const Rect &a, const Rect &b) {
	return a.c < b.c;
}

int64 ans[8];
int color[8];
Rect rc[10003];

void dfs(int x1, int y1, int x2, int y2, int i, int c) {
	if (x1 >= x2 || y1 >= y2) return;
	if (i == -1) {
		if (c) {
			ans[c] += int64(x2 - x1) * (y2 - y1);
		}
		return;
	}
	if (0 <= i && i < color[1] && (c|1)==c) {
		dfs(x1, y1, x2, y2, -1, c);
		return;
	} else if (color[1] <= i && i < color[2] && (c|2)==c) {
		dfs(x1, y1, x2, y2, color[1]-1, c);
		return;
	} else if (color[2] <= i && i < color[4] && (c|4)==c) {
		dfs(x1, y1, x2, y2, color[2]-1, c);
		return;
	}
	if (x2 <= rc[i].x1 || y2 <= rc[i].y1 || x1 >= rc[i].x2 || y1 >= rc[i].y2) {
		dfs(x1, y1, x2, y2, i-1, c);
	} else {
		int k1 = max(x1, rc[i].x1);
		int k2 = min(x2, rc[i].x2);
		if (x1 < k1) dfs(x1, y1, k1, y2, i-1, c);
		if (k2 < x2) dfs(k2, y1, x2, y2, i-1, c);

		int k3 = max(y1, rc[i].y1);
		int k4 = min(y2, rc[i].y2);
		if (y1 < k3) dfs(k1, y1, k2, k3, i-1, c);
		if (k3 < y2) dfs(k1, k4, k2, y2, i-1, c);
		if (k1 < k2 && k3 < k4) dfs(k1, k3, k2, k4, i-1, c|rc[i].c);
	}
}

int main() {
	int runs;
	scanf("%d", &runs);
	for (int ca = 1; ca <= runs; ++ca) {
		int n, x = 0, y = 0;
		memset(ans, 0, sizeof(ans));
		memset(color, 0, sizeof(color));
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			char c[2];
			scanf("%s%d%d%d%d", c, &rc[i].x1, &rc[i].y1, &rc[i].x2, &rc[i].y2);
			if (c[0] == 'R') {
				rc[i].c = 1;
			} else if (c[0] == 'G') {
				rc[i].c = 2;
			} else if (c[0] == 'B') {
				rc[i].c = 4;
			}
			color[rc[i].c]++;
			x = max(rc[i].x2, x);
			y = max(rc[i].y2, y);
		}
		color[2] += color[1];
		color[4] += color[2];
		sort(rc, rc+n, cmp);
		dfs(0, 0, x, y, n-1, 0); /* 用一个很大的矩形盖住所有的东西 */
		printf("Case %d:\n", ca);
		for (int i = 0; i < 7; ++i) printf("%lld\n", ans[fx[i]]);
	}
	return 0;
}
