#include <stdio.h>
#include <string.h>
long long f[202][202];

long long F(int m, int n)
{
	if (m < 0) return 0;
	if (m == 0) return 1;
	if (n == 1) return 1;
	if (f[m][n] == -1) f[m][n] = F(m - n, n) + F(m, n-1);
	return f[m][n];
}

int main()
{
	int m, n;
	while (~scanf("%d %d", &m, &n) && m > 0 && n > 0) {
		memset(f, -1, sizeof(f));
		printf("%I64d\n", F(m-n, n));
	}
	return 0;
}
