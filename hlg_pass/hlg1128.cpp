#include <stdio.h>

int n, a, b, c, i;
int ar[100000+5];

int main()
{
	while (EOF != scanf("%d", &n)) {
		c = 0;
		for (i = 0 ; i < n; i++) {
			scanf("%d", &ar[i]);
			c ^= ar[i];
		}
		c = ((c ^ (c - 1)) + 1) >> 1;
		a = b = 0;
		for (i = 0; i < n; i++) {
			if (ar[i] & c) {
				a ^= ar[i];
			} else {
				b ^= ar[i];
			}
		}
		if (a > b) {
			a ^= b;
			b ^= a;
			a ^= b;
		}
		printf("%d %d\n", a, b);
	}
	return 0;
}

