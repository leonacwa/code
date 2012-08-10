/* Party All the Time
 * */
#include <cstdio>
#include <cstring>
#include <cmath>

const int MAXN = 50005;

int n;
double s[MAXN], w[MAXN];

double f(double x) {
	double ret = 0, t;
	for (int i = 0; i < n; ++i) {
		t = fabs(s[i] - x);
		ret += t * t * t * w[i];
	}
	return ret;
}

int main() {
	int runs;
	scanf("%d", &runs);
	for (int run = 1; run <= runs; ++run) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf", &s[i], &w[i]);
		}
		double l = s[0], r = s[n-1];
		while (r - l > 0.0001) {
			double m = (l + r) / 2;
			double ml = (l + m) / 2;
			if (f(ml) > f(m)) {
				l = ml;
			} else {
				r = m;
			}
		}
		printf("Case #%d: %0.0f\n", run, f((l+r)/2));
		/*
		long long ans = (long long)(f((l+r)/2) + 0.5);
		printf("Case #%d: %lld\n", run, ans);
		*/
	}
	return 0;
}
