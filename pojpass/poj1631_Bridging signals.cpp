/*
 * POJ 1631 Bridging signals
 * */
#include <cstdio>
#include <cstring>

int h[40005];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int a, n, ans = 1;
		scanf("%d%d", &n, &a);
		h[1] = a;
		for (int i = 1; i < n; ++i) {
			scanf("%d", &a);
			int l = 1, r = ans;
			while (l <= r) {
				int m = (l + r) / 2;
				if (h[m] < a) {
					l = m + 1;
				} else {
					r = m - 1;
				}
			}
			h[l] = a;
			if (ans < l) ans = l;
		}
		printf("%d\n", ans);
	}
	return 0;
}
