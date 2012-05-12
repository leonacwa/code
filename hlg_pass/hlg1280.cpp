#include <stdio.h>

bool test(int a[], int l)
{
	if (a[0] == 0) {
		return false;
	}
	for (int i = l/2; i >= 0; i--) {
		if (a[i] != a[l-i-1]) {
			return false;
		}
	}
	return true;
}

int main()
{
	int num[64];
	int n, s, nCase = 0;
	while (~scanf("%d %d", &n, &s)) {
		printf("Case %d:\n", ++nCase);
		for (int i = s+1; n > 0; i++) {
			int  cnt = 0;
			for (int d = 2; d <= 10; d++) {
				int l = 0, t = i;
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

