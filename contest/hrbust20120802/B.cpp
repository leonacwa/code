#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 * 判断点是否在线段上 语法：result=Pointonline(Point p1,Point p2,Point p);
 * 参数：
 * p1、p2：线段的两个端点
 * p：被判断点
 * 返回值：0：点在不在线段上；1：点在线段上
 * 注意： 若p线段端点上返回1
 */
typedef long long int64;
const double eps = 1e-8;
struct Point {
	int64 x,y;
};

int64 cross(Point p2, Point p1, Point p0) {
	return (p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y);
}

int PointOnLine(Point p1,Point p2,Point p) {
	if (cross(p, p2, p1) != 0) return false;
	return (min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x) && min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y));
}

int PointInCircle(Point pc, int64 r, Point p) {
#define sq(x) ((x) * (x))
	int64 d2 = sq(pc.x - p.x) + sq(pc.y - p.y);
	return d2 <= r * r;
}

int main() {
	int x, y, r;
	Point sp, tf0, tf1, jj;
	while (EOF != scanf("%d%d%d", &x, &y, &r)) {
		sp.x = x, sp.y = y;

		scanf("%d%d", &x, &y);
		tf0.x = x, tf0.y = y;
		scanf("%d%d", &x, &y);
		tf1.x = x, tf1.y = y;

		scanf("%d%d", &x, &y);
		jj.x = x, jj.y = y;

		/*
		printf ("%d\n", PointInCircle(sp, r, tf0));
		printf("%d\n",  PointOnLine(tf0, tf1, jj));
		printf("%d\n", PointInCircle(sp, r, jj));
		*/
		//if ((PointInCircle(sp, r, tf0) && PointOnLine(tf0, tf1, jj)) || PointInCircle(sp, r, jj)) puts("DEAD");
		if (PointOnLine(tf0, tf1, jj) || PointInCircle(sp, r, jj)) puts("DEAD");
		else puts("LIVE");
	}
	return 0;
}
