/* Pie
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10005;
const double eps = 1e-6;
const double PI = acos(-1);

int n, f;
double a[MAXN], ra[MAXN];

bool check(double v) {
	int sum = 0;
	for (int i = n-1; i >= 0; --i) {
		if (a[i] >= v) sum += (int)(a[i] / v);
		if (sum > f) return true;
	}
	return sum > f;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		double l = 0, r = 0;
		scanf("%d%d", &n, &f);
		for (int i = 0; i < n; ++i) {
			scanf("%lf", &ra[i]);
			a[i] = ra[i] * ra[i] * PI;
			r += a[i];
		}
		sort(a, a + n);
		r /= (f + 1);
		while (fabs(r-l) >= eps) {
			double m = (l + r) / 2;
			if (check(m)) {
				l = m;
			} else {
				r = m;
			}
		}
		printf("%0.4lf\n", (l+r)/2);
	}
	return 0;
}

