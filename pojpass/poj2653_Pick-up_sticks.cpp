/* POJ2653 Pick-up sticks
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
using namespace std;


const double eps = 1e-8;

struct Point {
	double x, y;
	Point() {}
	Point(double tx, double ty) : x(tx), y(ty) {}
};
struct Line {
	Point p, q;
	int id;
	Line() {}
	Line(Point tp, Point tq) : p(tp), q(tq) {}
};
typedef list<Line> listLine;
typedef list<Line>::iterator listLineIt;

bool operator == (const Point &A, const Point &B) {
	return A.x == B.x && A.y == B.y;
}

bool operator != (const Point &A, const Point &B) {
	return A.x != B.x || A.y != B.y;
}

bool operator < (const Point &A, const Point &B) {
	if (A.x != B.x) return A.x < B.x;
	return A.y < B.y;
}

double cross(Point p, Point q, Point p0) {
	return (p.x - p0.x) * (q.y - p0.y) - (q.x - p0.x) * (p.y - p0.y);
}
// 两个线段p, q相交
bool isSegInter(Point p1, Point p2, Point q1, Point q2) {
	return (
			min(p1.x, p2.x) <= max(q1.x, q2.x) &&
			min(q1.x, q2.x) <= max(p1.x, p2.x) &&
			min(p1.y, p2.y) <= max(q1.y, q2.y) &&
			min(q1.y, q2.y) <= max(p1.y, p2.y) &&
			cross(p1, q2, q1) * cross(p2, q2, q1) <= 0 &&
			cross(q1, p2, p1) * cross(q2, p2, p1) <= 0 
		   );
}

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		listLine li;
		Point p, q;
		Line l;
		scanf("%lf%lf%lf%lf", &p.x, &p.y, &q.x, &q.y);
		l = Line(p, q);
		l.id = 1;
		li.push_back(l);
		for (int i = 2; i <= n; ++i) {
			scanf("%lf%lf%lf%lf", &p.x, &p.y, &q.x, &q.y);
			for (listLineIt it = li.begin(); it != li.end(); ) {
				if (isSegInter(p, q, it->p, it->q)) {
					it = li.erase(it);
				} else {
					++it;
				}
			}
			l = Line(p, q);
			l.id = i;
			li.push_back(l);
		}
		printf("Top sticks:");
		for (listLineIt it = li.begin(); it != li.end(); ++it) {
			listLineIt it2 = it;
			++it2;
			printf(" %d", it->id);
			printf(it2 == li.end() ? "." : ",");
		}
		puts("");
	}
	return 0;
}

