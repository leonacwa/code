/*
 * POJ 3903 Stock Exchange
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 100005;

int h[MAXN];

int main() {
	int n, a;
	while (EOF != scanf("%d", &n)) {
		scanf("%d", &a);
		int ans = 1;
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
