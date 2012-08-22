#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int NN = 601;
bool ma[NN][NN];
int r, c;

struct Point {
	int x, y;
	Point(int tx = 0, int ty = 0) : x(tx), y(ty)
	{}
};

bool d_link(Point a, Point b)
{
	if (a.x == b.x) {
		if (a.y > b.y) swap(a, b);
		for (int y = a.y+1; y < b.y; ++y) {
			if (ma[a.x][y]) return false;
		}
	} else if (a.y == b.y) {
		if (a.x > b.x) swap(a, b);
		for (int x = a.x+1; x < b.x; ++x) {
			if (ma[x][a.y]) return false;
		}
	} else {
		return false;
	}
	return true;
}

bool test(Point p1, Point p2)
{
	if (p1.y > p2.y) swap(p1,p2);
	for (int x = 0; x < r; ++x) {
		if ((p1.x == x || !ma[x][p1.y]) && (x == p2.x || !ma[x][p2.y]) && d_link(p1, Point(x, p1.y)) && d_link(Point(x, p1.y), Point(x, p2.y)) && d_link(Point(x, p2.y), p2)) {
			return true;
		}
	}
	if (p1.x > p2.x) swap(p1, p2);
	for (int y = 0; y < c; ++y) {
		if ((p1.y == y || !ma[p1.x][y]) && (y == p2.y || !ma[p2.x][y]) && d_link(p1, Point(p1.x, y)) && d_link(Point(p1.x, y), Point(p2.x, y)) && d_link(Point(p2.x, y), p2)) {
			return true;
		}
	}
	return false;
}

int main()
{
	while (EOF != scanf("%d %d", &r, &c)) {
		memset(ma, 0, sizeof(ma));
		int b, q;
		scanf("%d", &b);
		for (int i = 0; i < b; ++i) {
			int x, y;
			scanf("%d %d", &x, &y);
			ma[x][y] = true;
		}
		scanf("%d", &q);
		int score = 60;
		for (int i = 0; i < q; ++i) {
			int sx, sy, ex, ey;
			scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
			if (ma[sx][sy] && ma[ex][ey] && test(Point(sx, sy), Point(ex, ey))) {
				score += 2;
				ma[sx][sy] = false;
				ma[ex][ey] = false;
			} else {
				score -= 1;
			}
			printf("%d\n", score);
		}
	}
	return 0;
}

