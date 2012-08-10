#include <cstdio>
#include <cstring>
#include <iostream>

int ys[100005];

int main()
{
	int k, n;
	while (EOF != scanf("%d%d", &k, &n)) {
		int y, s, win = 0;;
		memset(ys, -1, sizeof(ys));
		scanf("%d%d", &y, &s);
		int tot = n + k - 2;
		for (int i = 0, a, b; i < tot; ++i) {
			scanf("%d%d", &a, &b);
			if (a <= y) {
				if (b <= s) ++win;
			} else {
				ys[a - y] = b;
			}
		}
		int i = 0;
		if (win < k-1) {
			for (i = 1; ys[i] != -1; ++i) {
				if (ys[i] <= s) ++win;
				if (win >= k-1) break;
			}
		}
		if (win >= k-1) printf("%d\n", y + i);
		else puts("unknown");
	}
	return 0;
}
