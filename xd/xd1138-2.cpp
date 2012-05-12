#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

map<long long, int> cnt;
long long a[100005];

int main()
{
	int C;
	scanf("%d", &C);
	while (C--) {
		int n;
		long long m;
		cnt.clear();
		scanf("%d %lld", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			cnt[a[i]]++;
		}
		long long ans = 0;
		for (int i = 0; i < n; ++i) {
			long long x = a[i];
			long long y = m - a[i];
			if (x == y)
				ans += cnt[y]-1;
			else
				ans += cnt[y];
		}
		printf("%lld\n", ans / 2);
	}
	return 0;
}

