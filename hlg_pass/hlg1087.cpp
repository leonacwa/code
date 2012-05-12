#include <stdio.h>

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, sum = 0, t;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &t);
			sum += t;
		}
		if (sum%(n-1) == 0 && sum/(n-1)<=n) {
			printf("%d\n", sum / (n-1));
		} else {
			printf("-1\n");
		}
	}
	return 0;
}

