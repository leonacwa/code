#include <stdio.h>

int test(int a[], int l)
{
	int i;
	if (a[0] == 0) {
		return 0;
	}
	for (i = l/2; i >= 0; i--) {
		if (a[i] != a[l-i-1]) {
			return 0;
		}
	}
	return 1;
}

int main()
{
	int num[64];
	int d, cnt, l, t, i, n, s, nCase = 0;
	while (~scanf("%d %d", &n, &s)) {
		printf("Case %d:\n", ++nCase);
		for (i = s+1; n > 0; i++) {
			cnt = 0;
			for (d = 2; d <= 10; d++) {
				l = 0, t = i;
				while (t >= d) {
					num[l++] = t % d;
					t /= d;
				}
				num[l++] = t;
				if (test(num, l)) {
					cnt++;
				}
				if (cnt >= 2) {
					printf("%d\n", i);
					n--;
					break;
				}
			}
		}
	}
	return 0;
}

