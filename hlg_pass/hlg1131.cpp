#include <stdio.h>

int a[30000+5];
int main()
{
	int nCase;
	scanf("%d", &nCase);
	while (nCase--) {
		int n, aa, bb, cnt = 0;
		scanf("%d", &n);
		if (n == 0) {
			puts("0");
			continue;
		}
		scanf("%d", &a[0]);
		aa = 0;
		cnt = 1;
		for (int i = 1; i < n; i++) {
			scanf("%d", &a[i]);
			if (a[i-1] > a[i]) {
				bb = 1;
			} else {
				bb = 0;
			}
			if (aa != bb) {
				cnt++;
			}
			aa = bb;
		}
		printf("%d\n", cnt);
	}
	return 0;
}

