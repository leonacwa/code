#include <cstdio>

int main()
{
	int f, n;
	scanf("%d", &f);
	while (f--) {
		scanf("%d", &n);
		printf("%d\n", (n / 2) * ((n - 1) / 2));
	}
	return 0;
}

