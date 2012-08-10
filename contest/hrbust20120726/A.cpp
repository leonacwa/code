#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int a[1005];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		sort(a, a+n);
		int ans = 0, t;
		for (int i = 0; i < n; ++i) {
			t = (n - i) * a[i];
			if (ans < t) ans = t;
		}
		printf("%d\n", ans);
	}
	return 0;
}

