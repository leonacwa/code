#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXRC = 5000;
const int MAXN = 5000+5;

struct Point {
	int x, y;
	Point(int xt = 0, int yt = 0) {
		x = xt;
		y = yt;
	}
	bool operator <(const Point& b) const {
		if (x == b.x) return y < b.y;
		return x < b.x;
	}
	bool operator == (const Point& b) const {
		return x == b.x && y == b.y;
	}
	Point operator - (const Point& b) const {
		return Point(x - b.x, y - b.y);
	}
	Point operator + (const Point& b) const {
		return Point(x + b.x, y + b.y);
	}
};

Point pt[MAXN];
int n, R, C;
bool g[MAXRC+1][MAXRC+1];

int main()
{
	while (EOF != scanf("%d %d", &R, &C)) {
		scanf("%d", &n);
		memset(g, 0, sizeof(0));
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &pt[i].x, &pt[i].y);
			g[pt[i].x][pt[i].y] = true;
		}
		sort(pt, pt+n);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				Point v = pt[j] - pt[i];
				Point oa = pt[i] - v;
				Point p = pt[j];
				int k = 1;
				if (!(0 < oa.x && oa.x <= R && 0 < oa.y && oa.y <= C)) {
					while (0 < p.x && p.x <= R && 0 < p.y && p.y <= C && g[p.x][p.y]) { //binary_search(pt, pt+n, p)) {
						p = p + v;
						k++;
					}
				}
				if (!(0 < p.x && p.x <= R && 0 < p.y && p.y <= C)) {
					if (ans < k) {
						ans = k;
					}
				}
			}
		}
		if (ans < 3) {
			ans = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}

