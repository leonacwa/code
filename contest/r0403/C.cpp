#include <cstdio>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

int a[13];
int n, k;

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d", &k);
		for (int i = 0; i < 12; ++i) scanf("%d", &a[i]);
		sort(a, a+12, greater<int>());
		int sum = 0, i;
		for (i = 0; i < 12; ++i) {
			if (sum < k) {
				sum += a[i];
			} else break;
		}
		if (sum >= k) printf("%d\n", i);
		else puts("-1");
	}
	return 0;
}

