#include <stdio.h>

int main()
{
	int n, m;
	while (EOF != scanf("%d %d", &n, &m)) {
		if (m <= (n-1)*(n-2)/2) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}

