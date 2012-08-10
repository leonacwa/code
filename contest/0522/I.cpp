#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;
int a[MAXN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		sort(a, a+n);
		int ans = 0;
		int i = 0;
		while (i < n) {
			int cnt = 1;
			while (i < n && a[i] == a[i+1]) {
				++cnt;
				++i;
			}
			++i;
			if (ans < cnt) ans = cnt;
		}
		printf("%d\n", ans);
	}
	return 0;
}

