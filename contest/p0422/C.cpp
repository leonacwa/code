#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, a, b;
		scanf("%d %d %d", &n, &a, &b);
		int ans = min(n - a, b + 1);
		if (ans < 0) ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}


