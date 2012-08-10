#include <cstdio>
#include <climits>

int main()
{
	int n, m, u, d;
	while (EOF != scanf("%d%d", &n, &m)) {
		int ans = INT_MAX;
		for (int i = 0; i < m; ++i) {
			scanf("%d%d", &u, &d);
			int x = (int)((1.0 * d * n) / (u + d) + 1.0);
			int y = n - x;
			if (u * x - d * y < ans) ans = u * x - d * y;
		}
		printf("%d\n", ans);
	}
	return 0;
}

