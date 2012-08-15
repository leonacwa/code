/* Lineland's Airport
 * 三分
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 505;
int n;
double L, x[MAXN], y[MAXN];

double area(double xx, int i) {
	//while (x[i+1] < xx) ++i;
	if (x[i+1] >= xx+L) {
		double y1 = y[i] + (y[i+1] - y[i]) * (xx - x[i]) / (x[i+1] - x[i]);
		double y2 = y[i] + (y[i+1] - y[i]) * (xx+L - x[i]) / (x[i+1] - x[i]);
		return L * fabs(y2 - y1) / 2;
	}
	double yy = y[i] + (y[i+1] - y[i]) * (xx - x[i]) / (x[i+1] - x[i]);
	double res = (x[i+1] - xx) * (yy + y[i+1]) / 2;
	double low = min(yy, y[i+1]);
	++i;
	while (x[i+1] < xx + L) {
		res += (x[i+1] - x[i]) * (y[i] + y[i+1]) / 2;
		if (low > y[i+1]) low = y[i+1];
		++i;
	}
	yy = y[i] + (y[i+1] - y[i]) * (xx+L - x[i]) / (x[i+1] - x[i]);
	res += (xx+L - x[i]) * (y[i] + yy) / 2;
	if (low > yy) low = yy;
	return res - low * L;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d%lf", &n, &L);
		for (int i = 0; i < n; ++i) scanf("%lf%lf", &x[i], &y[i]);
		double ans = 1e100;
		for (int fr = 0; fr < n-1; ++fr) {
			for (int ta = fr; ta < n-1; ++ta) {
				if (x[ta] - x[fr+1] > L) break;//continue;
				if (x[ta+1] - x[fr] < L) continue;
				double lo = max(x[fr], x[ta]-L), hi = min(x[fr+1], x[ta+1]-L);
				while (fabs(hi - lo) > 1e-6) { // 精度必须很高
					// 因为是凹函数，使用三分查找
					double x1 = (lo*2 + hi) / 3;
					double x2 = (lo + hi*2) / 3;
					if (area(x1, fr) < area(x2, fr)) {
						hi = x2;
					} else {
						lo = x1;
					}
				}
				double a = area(lo, fr);
				if (ans > a) ans = a;
			}
		}
		printf("%.4lf\n", ans);
	}
	return 0;
}
