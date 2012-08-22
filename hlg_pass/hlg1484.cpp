#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

int a[1005];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int p, n;
		scanf("%d%d", &p, &n);
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		sort(a, a + n, greater<int>());
		int d = n / (p + 1), sum = 0;
		for (int i = 0; i < d; ++i) sum += a[i];
		printf("%d\n", sum);
	}
	return 0;
}

