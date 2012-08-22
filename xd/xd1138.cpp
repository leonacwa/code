#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN (100000+128)
struct A {
	long long a;
	long long c;
	bool operator < (const A &b) const {
		return a < b.a;
	}
};
A a[MAXN];

int b_s(A a[], int n, long long x) {
	int l = 0, r = n - 1, m;
	while (l < r) {
		m = (r - l) / 2 + l;
		if (a[m].a < x)
			l = m + 1;
		else
			r = m;
	}
	if (a[l].a == x)
		return l;
	return -1;
}

int main()
{
	int C, n, i, t, j;
	long long ans;
	long long m;
	scanf("%d", &C);
	while (C--) {
		scanf("%d %lld", &n, &m);
		for (i = 0; i < n; ++i) {
			scanf("%lld", &a[i].a);
		}
		sort(a, a+n);
		j = 0;
		a[0].c = 1;
		for (i = 1; i < n; ++i) {
			if (a[j].a == a[i].a) {
				a[j].c++;
			}
			else {
				++j;
				a[j].a = a[i].a;
				a[j].c = 1;
			}
		}
		n = j + 1;
		ans = 0;
		for (i = 0; i < n; ++i) {
			if (a[i].a == m - a[i].a) {
				ans += a[i].c * (a[i].c - 1);
			} else {
				t = b_s(a, n, m - a[i].a);
				if (-1 != t) {
					ans += a[i].c * a[t].c;
				} 
			}
		}
		printf("%lld\n", ans / 2);
	}
	return 0;
}

