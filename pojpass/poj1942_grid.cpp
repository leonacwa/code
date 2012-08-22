#include <stdio.h>

long long C(long long n, long long m)
{
	if (n > m - n) n = m - n;
	long long ret = 1, cnt = n;
	while (cnt > 0) {
		--cnt;
		ret *= m --;
		while (ret % n == 0 && n > 1) {
			ret /= n --;
		}
	}
	return ret;
}

int main()
{
	long long n, m;
	while (EOF != scanf("%I64d %I64d", &n, &m)) {
		if (n == 0 && m == 0) break;
		printf("%I64d\n", C(m, n+m));
	}
	return 0;
}