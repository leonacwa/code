/* POJ 2398 Toy Storage
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
	Point() {}
	Point(int tx, int ty) : x(tx), y(ty) {}
};

struct Line {
	Point p, q; // down up
	Line(){}
	Line(Point tp, Point tq) : p(tp), q(tq) {}
	bool operator < (const Line &B) const {
		return p.x < B.p.x;
	}
};

int cross(Point p, Point q, Point p0) {
	return (p.x - p0.x) * (q.y - p0.y) - (q.x - p0.x) * (p.y - p0.y);
}

const int MAXN = 1005;

Line li[MAXN];
int cnt[MAXN], cnt2[MAXN];

int binSearch(int n, Line li[], Point p) {
	int l = 0, r = n - 1, m;
	while (l < r - 1) {
		m = (l + r) >> 1;
		if (cross(p, li[m].q, li[m].p) < 0) {
			r = m;
		} else {
			l = m;
		}
	}
	if (cross(p, li[l].q, li[l].p) > 0 && cross(p, li[l+1].q, li[l+1].p) < 0) return l;
	return -1;
}

int main() {
	int n, m, x1, x2, y1, y2;
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		scanf("%d%d%d%d%d", &m, &x1, &y1, &x2, &y2);
		int tot = 2;
		li[0] = Line(Point(x1, y2), Point(x1, y1));
		li[1] = Line(Point(x2, y2), Point(x2, y1));
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &x1, &x2);
			li[tot++] = Line(Point(x2, y2), Point(x1, y1));
		}
		sort(li, li + tot);
		memset(cnt, 0, sizeof(cnt));
		memset(cnt2, 0, sizeof(cnt2));
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &x1, &y1);
			int j = binSearch(tot, li, Point(x1, y1));
			if (j != -1) ++cnt[j];
		}
		for (int i = 0; i < tot; ++i) {
			++cnt2[cnt[i]];
		}
		puts("Box");
		int sum = 0;
		for (int i = 1; i <= m; ++i) {
			if (cnt2[i]) {
				printf("%d: %d\n", i, cnt2[i]);
				sum += cnt2[i];
				if (sum == m) break;
			}
		}
	}
	return 0;
}
