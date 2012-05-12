#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
};

bool cmpPoint(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y > 0;
}
Point ap[100], p;
int n;

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		scanf("%d %d", &p.x, &p.y);
		for (int i = 1; i < n; ++i) {
			scanf("%d %d", &ap[i].x, &ap[i].y);
		}
		sort(ap+1, ap + n, cmpPoint);
		for (int i = 0; i < n; ++i) {
			printf("(%d,%d)\n", ap[i].x, ap[i].y);
		}
	}
	return 0;
}

