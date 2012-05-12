#include <stdio.h>

int main()
{
	int s, n;
	while (~scanf("%d", &n)) {
		s = 1;
		for (int i = 2; i <= n; i++) {
			s *= i;
		}
		printf("%d\n", s);
	}
	return 0;
}

