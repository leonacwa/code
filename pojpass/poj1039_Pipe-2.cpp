/*
 * 枚举两个坐标构成的直线，需要判断是否能从之前的pipe通过，然后再看能不能通过后面的，不能的计算最远距离。
 * */
#include <stdio.h>
#include <math.h>
const double EPS = 1e-8;
const double MAX_DBL = 1e12;
double X[64], Y[64];
int n;

void cross_point(double &x, double &y, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	x = ((x4*y3-x3*y4)/(x4-x3) - (x2*y1-x1*y2)/(x2-x1)) / ((y2-y1)/(x2-x1) - (y4-y3)/(x4-x3));
	y = (x*(y2-y1) - x1*y2 + x2*y1) / (x2 - x1);
}

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &X[i], &Y[i]);
		}
		double max_x = -MAX_DBL, right, x, y;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				double xi = X[i], xj = X[j], yi = Y[i], yj = Y[j]-1.0;
				right = -MAX_DBL;
				for (int k = 0; k < n; k++) {
					x = X[k];
					// y = (x*(yj - yi) + xj*yi - xi*yj) / (xj - xi);
					y = (x - xj)*(yj - yi) / (xj - xi) + yj;
					if ((Y[k]-1.0 < y && y < Y[k]) || fabs(Y[k]-1.0-y) < EPS || fabs(Y[k]-y) < EPS) {
						right = x;
					} else {
						if (k > 0) {
							if (y < Y[k]-1.0) {
								cross_point(x, y, xi, yi, xj, yj, X[k-1], Y[k-1]-1.0, X[k], Y[k]-1.0);
							} else {
								cross_point(x, y, xi, yi, xj, yj, X[k-1], Y[k-1], X[k], Y[k]);
							}
						}
						right = x;
						break;
					}
				}
				if (max_x < right) {
					max_x = right;
				}
			}
		}
		if (max_x >= X[n-1] || fabs(max_x - X[n-1]) < EPS) {
			printf("Through all the pipe.\n");
		} else {
			printf("%.2lf\n", max_x);
		}
	}
	return 0;
}
