#include <stdio.h>

int peach(int n)
{
	if (n == 1)
		return 1;
	else
		return (peach(n-1)+1)*2;
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		printf("%d\n", peach(n));
	}
	return 0;
}
