#include <stdio.h>
#include <math.h>

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		double l1, l2, l3;
		scanf("%lf %lf %lf", &l1, &l2, &l3);
		double a = 1 / (1 + l1);
		double b = 1 / (1 + l2);
		double c = 1 / (1 + l3);
		double h = 1.0 / 2 * sqrt(3.0);
		double ans = 1.0 / 4 * sqrt(3.0) - a * (l2 / (1+l2)) * h * 0.5 - b * (l3 / (1+l3)) * h * 0.5 - c * (l1 / (1+l1)) * h * 0.5;
		printf("%.4lf\n", ans);
	}
	return 0;
}
