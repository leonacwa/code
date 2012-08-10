#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int c[101];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &c[i]);
		}
		sort(c, c + n);
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			if (c[i] < 0 && i < m) {
				ans -= c[i];
			} else {
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}


