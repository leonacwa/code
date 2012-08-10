/* Containers
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int64_t Labs(int64_t a) {
	return a < 0 ? -a : a;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int64_t n, a, b, area = 0x7fffffffffffffffLL;
		int ey;
		scanf("%lld", &n);
		ey = (int)(sqrt(n+.0)) + 1;
		for (int y = 1; y <= ey; ++y) { // 10^6
			int x = (n - 1) / (5 * y) + 1;
			if (5LL * x * y < n) continue;
			int64_t t1 = 10LL * x + 2, t2 = 44LL * y + 4;
			int64_t t3 = t1 * t2;
			if (t3 < area) {
				a = t1, b = t2, area = t3;
			} else if (t3 == area) {
			   	if (Labs(t1 - t2) < Labs(a - b)) {
					a = t1, b = t2, area = t3;
				}
			}
		}
		if (b < a) swap(b, a);
		printf("%lld X %lld = %lld\n", b, a, area);
	}
	return 0;
}
