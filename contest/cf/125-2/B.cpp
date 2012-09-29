#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
};

int dist2(Point p1, Point p2) {
	int dx = p1.x - p2.x, dy = p1.y - p2.y;
	return dx * dx + dy * dy;
}
int sq(int x) {
	return x * x;
}

bool inCircle(int d2, int r1, int r2) {
	return r1 <= r2 && d2 <= sq(r1 - r2);
}

bool outCircle(int d2, int r1, int r2) {
	if (d2 >= sq(r1+r2)) return true;
	return inCircle(d2, r1, r2);
}

int main()
{
	Point p1, p2;
	int r1, R1, r2, R2;
	while (EOF != scanf("%d%d%d%d", &p1.x, &p1.y, &r1, &R1)) {
		scanf("%d%d%d%d", &p2.x, &p2.y, &r2, &R2);
		int d2 = dist2(p1, p2), ans = 0;
		if (inCircle(d2, r1, r2) || outCircle(d2, R2, r1)) ++ans;
		if (inCircle(d2, R1, r2) || outCircle(d2, R2, R1)) ++ans;
		if (inCircle(d2, r2, r1) || outCircle(d2, R1, r2)) ++ans;
		if (inCircle(d2, R2, r1) || outCircle(d2, R1, R2)) ++ans;
		printf("%d\n", ans);
	}
	return 0;
}

