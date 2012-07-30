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
Point ap[200];
int n;

int main()
{
	int n = 0;
	while (EOF != scanf("%d %d", &ap[n].x, &ap[n].y)) {
		++n;
	}
	sort(ap+1, ap + n, cmpPoint);
	for (int i = 0; i < n; ++i) {
		printf("(%d,%d)\n", ap[i].x, ap[i].y);
	}
	return 0;
}
