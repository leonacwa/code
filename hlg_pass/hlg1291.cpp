#include <stdio.h>

struct Point {
	int x, y;
};

Point ap[105], p;
int n;

int cross_procduct(Point p0, Point p1, Point p2)
{
	return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

int main()
{
	while (EOF != scanf("%d %d %d", &n, &p.x, &p.y)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &ap[i].x, &ap[i].y);
		}
		bool can = true;
		for (int i = 0; i < n; ++i) {
			int j = (i+1) % n;
			if (cross_procduct(ap[i], p, ap[j]) > 0) {
				can = false;
				break;
			}
		}
		printf("%s\n", can ? "Yes" : "No");
	}
	return 0;
}

