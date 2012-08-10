#include <cstdio>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

int n, m, k;
int a[10*100+10];

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d %d", &n, &m, &k)) {
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &a[cnt++]);
			}
		}
		sort(a, a+cnt, greater<int>());
		printf("Scenario #%d\n%d\n\n", ++nCase, a[k-1]);
	}
	return 0;
}

