#include <cstdio>
#include <cstring>

struct Point {
	int x, y;
};
int abs(int a) {
	return a < 0 ? -a : a;
}

int gcd(int a, int b) {
	int t;
	while (b) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}
int PointOnEdge(int n, Point p[]) {
	int i, ret = 0;
	for (i = 0; i < n; ++i) {
		ret += gcd(abs(p[i].x - p[(i+1)%n].x), abs(p[i].y - p[(i+1) % n].y));
	}
	return ret;
}
int PointInPolygon(int n, Point p[]) {
	int i, area = 0;
	for (i = 0; i < n; ++i) {
		//area += p[(i+1) % n].y * (p[i].x - p[(i+2) % n].x); // 如果将式子展开，可以简化成这个样子，减小运算量
		area += p[i].x * p[(i+1)%n].y - p[i].y * p[(i+1) % n].x;
	}
	return (abs(area) - PointOnEdge(n, p)) / 2 + 1;
}

Point pt[10005];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n;
		scanf("%d", &n);
		Point tp;
		tp.x = 0, tp.y = 0;
		for (int i = 0, x, y; i < n; ++i) {
			scanf("%d%d", &x, &y);
			pt[i].x = x + tp.x, pt[i].y = y + tp.y;
			tp = pt[i];
		}
		printf("%d\n", PointInPolygon(n, pt));
	}
	return 0;
}
