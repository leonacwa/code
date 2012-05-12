#include <stdio.h>
#include <math.h>

int main()
{
	int x, y, x1, y1, x2, y2, v;
	while (~scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &v)) {
		x = x1 - x2;
		y = y1 + y2;
		printf("%.2lf\n", sqrt(0.0 + x*x + y*y) / v);
	}
	return 0;
}

