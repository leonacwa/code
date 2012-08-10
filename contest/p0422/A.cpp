#include <cstdio>

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%s\n", a > b ? "YES" : "NO");
	}
	return 0;
}

