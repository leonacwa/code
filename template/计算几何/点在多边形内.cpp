#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct Point {
	int x, y;
	Point() {}
	Point(int tx, int ty) : x(tx), y(ty) {}
};

int cross(Point p, Point q, Point p0) {
	return (p.x - p0.x) * (q.y - p0.y) - (q.x - p0.x) * (p.y - p0.y);
}
// 点p在<p1, p2>线段上
bool isPointOnSeg(Point p, Point p1, Point p2) {
	return (
			0 == cross(p, p1, p2) && 
			min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x) &&
			min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y) 
		   );
}
// 线段<p1, p2> <q1, q2> 相交，含顶点相交
bool isSegInter(Point p1, Point p2, Point q1, Point q2) {
	return (
			min(p1.x, p2.x) <= max(q1.x, q2.x) &&
			min(q1.x, q2.x) <= max(p1.x, p2.x) &&
			min(p1.y, p2.y) <= max(q1.y, q2.y) &&
			min(q1.y, q2.y) <= max(p1.y, p2.y) && /* 跨立实验 */
			cross(p1, q2, q1) * cross(p2, q2, q1) <= 0 && 
			cross(q1, p2, p1) * cross(q2, p2, p1) <= 0  /* 叉积相乘判方向 */
		   );
}
// 点pa是否在多边形内部，包括在边上，pt[]数组必须有序，如果无序，可以极角排序使之有序
bool isPointInPolygon(int n, Point pt[], Point pa) {
	int cnt = 0;
	Point pb = pa;/* pa, pb 构成一条射线 */
	for (int i = 0; i < n; ++i) if (pb.x > pt[i].x) pb.x = pt[i].x;
	--pb.x; // 假想的射线，注意叉积时不要超范围
	for (int i = 0; i < n; ++i) {
		int ii = (i + 1) % n;
		if (isPointOnSeg(pa, pt[i], pt[ii])) return true;
		if (pt[i].y == pt[ii].y) continue;
		/* 射线过边的y值最大的点*/
		int c1 = cross(pt[i], pb, pa), c2 = cross(pt[ii], pb, pa);
		if (0 == c1 || 0 == c2) { // 射线过一个顶点,则就只能算过顶点的
			if (
				(c1 == 0 && pt[i].y > pt[ii].y && pt[i].x <= pa.x) || 
				(c2 == 0 && pt[i].y < pt[ii].y && pt[ii].x <= pa.x)	 ) {
				++cnt;
			}
		} else if (isSegInter(pa, pb, pt[i], pt[ii])) {
			++cnt;
		}
	}
	return cnt & 1;
}

