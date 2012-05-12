#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 101;
struct Point {
	int x, y;
} pt[NN];

int cross(Point p2, Point p1, Point p0)
{
	return (p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y);
}

bool inPolygon(Point pa, Point pt[], int n)
{
	int cnt = 0;
	Point pb = pa;
	for (int i = 0; i < n; ++i) {
		if (pb.x > pt[i].x) {
			pb.x = pt[i].x;
		}
	}
	--pb.x;
	for (int i = 0; i < n; ++i) {
		int ii = (i + 1) % n;
		if (0 == cross(pa, pt[ii], pt[i]) && 
			min(pt[i].x, pt[ii].x) <= pa.x && pa.x <= max(pt[i].x, pt[ii].x) &&
			min(pt[i].y, pt[ii].y) <= pa.y && pa.y <= max(pt[i].y, pt[ii].y)) {
			return true;
		}
		if (pt[i].y != pt[ii].y) {
			int c1 = cross(pt[i], pb, pa), c2 = cross(pt[ii], pb, pa);
			if (0 == c1 || 0 == c2) {
				if ((c1 == 0 && (pt[i].y > pt[ii].y && pt[i].x <= pa.x)) || (c2 == 0 && pt[i].y < pt[ii].y && pt[ii].x <= pa.x)) {
					++cnt;
				}
			} else if (cross(pt[i], pb, pa) * cross(pb, pt[ii], pa) >= 0 && 
					cross(pb, pt[ii], pt[i]) * cross(pt[ii], pa, pt[i]) >= 0) {
				++cnt;
			}
		}
	}
	if (cnt % 2 == 1) return true;
	return false;
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n) && n > 0) {
		Point pa;
		scanf("%d %d", &pa.x, &pa.y);
		for (int i= 0; i < n; ++i) {
			scanf("%d %d", &pt[i].x, &pt[i].y);
		}
		puts(inPolygon(pa, pt, n) ? "Yes" : "No");
	}
	return 0;
}

