#include <stdio.h>

int main()
{
	int n;
	while (~scanf("%d", &n)) {
		n %= 3;	
		printf("%d\n", (n*n*n*n*n)%3);
	}
	return 0;
}

