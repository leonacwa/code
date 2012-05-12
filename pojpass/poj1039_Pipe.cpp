#include <stdio.h>
#include <math.h>
#include <float.h>
const double EPS = 1e-8;
//const double MAX_DBL = 1e300;

double ax[64], ay[64];
int n;

double xin(double k, double x0, double y0, double x1, double y1, double x2, double y2)
{
	return (x2 * y1 - x1 * y2 - (x2 - x1) * (y0 - k * x0)) / (k * (x2 - x1) + (y1 - y2));
}

double check(double x0, double y0)
{
	double k1, k2, l1, l2;
	k1 = DBL_MAX;
	k2 = -DBL_MAX; 
	for (int i = 0; i < n; ++i) { 
		if (ax[i] == x0) continue;
		l1 = (ay[i] - y0) / (ax[i] - x0);
		l2 = (ay[i] - 1.0 - y0) / (ax[i] - x0);
		/**
		if (fabs(l1) < EPS) l1 = 0.0;
		if (fabs(l2) < EPS) l2 = 0.0;
		/**/
		// 要注意两个斜率的注意范围，有一个错就全部错了
		if (l1 < l2) {
			if (l1 > k1 || l2 < k2) return ax[0];
			if (k1 > l2) k1 = l2;
			if (k2 < l1) k2 = l1;
		} else {
			if (l2 > k1) return xin(k1, x0, y0, ax[i-1], ay[i-1] - 1.0, ax[i], ay[i] - 1.0);
			if (l1 < k2) return xin(k2, x0, y0, ax[i-1], ay[i-1], ax[i], ay[i]);
			if (k1 > l1) k1 = l1;
			if (k2 < l2) k2 = l2;
		}
	}
	return ax[n-1];
}

int main()
{
	double ans, right;
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &ax[i], &ay[i]);
		}
		ans = ax[0] - 10000000;
		for (int i = 0; i < n; i++) {
			right = check(ax[i], ay[i]);
			if (ans < right) ans = right;
			right = check(ax[i], ay[i] - 1.0);
			if (ans < right) ans = right;
			if (ans == ax[n-1]) break;
		}
		if (ans == ax[n-1] || fabs(ans - ax[n-1]) < EPS) {
			printf("Through all the pipe.\n");
		} else {
			printf("%.2lf\n", ans);
		}
	}
	return 0;
}
