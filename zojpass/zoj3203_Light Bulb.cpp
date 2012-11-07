/*
 * ZOJ 3203 Light Bulb
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

double H, h, D;
double f(double x) {
	return h * D / H + x * H / (D + x) + h / H * x - x;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		//static int ncs = 0;
		//printf("Case %d\n", ++ncs);
		scanf("%lf%lf%lf", &H, &h, &D);
		double limit = D * h / (H - h);
		double ans = max(f(0.0), f(limit));
		//for (double x = 0.0; x <= limit; x += 0.001) printf("%lf %lf\n", x, f(x));
		double l = 0.0, r = limit;
		while (abs(r-l) >= 1e-8) {
			double m1 = (2 * l + r) / 3;
			double m2 = (l + 2 * r) / 3;
			if (f(m1) <= f(m2)) {
				l = m1;
			} else {
				r = m2;
			}
		}
		ans = max(ans, f(l));
		printf("%.3lf\n", ans);
	}
	return 0;
}
