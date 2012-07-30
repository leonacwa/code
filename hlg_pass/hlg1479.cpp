#include <cstdio>

int main()
{
	int runs, n, k, ans;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d%d", &n, &k);
		if (n == 1) ans = k / 2;
		else if (k < n + (n + 4) / 3) ans = k - n;
		else ans = (k - (n - 2) / 3) / 3;
		printf("%d\n", ans);
	}
	return 0;
}
