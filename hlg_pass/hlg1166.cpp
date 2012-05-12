#include <stdio.h>

int main()
{
	int a, b, c, d, e;
	while (~scanf("%d %d %d %d %d", &a, &b, &c, &d, &e)) {
		printf("%d\n", ( (a%e) * (b%e) * (c%e) * (d%e) )%e);
	}
	return 0;
}

