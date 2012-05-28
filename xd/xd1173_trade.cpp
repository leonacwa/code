#include <cstdio>
typedef long long llong;

llong ABS(llong x) {
	return x < 0 ? -x : x;
}

int main()
{
	int n;
	while (1 == scanf("%d", &n)) {
	//	while (n < 0) ;
		if (n == 0) break;
		int a;
		llong s = 0;
		llong ans = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a);
			s += a;
			ans += ABS(s);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

