#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int a[1000+5];

int main()
{
	int n, k;
	while (EOF != scanf("%d %d", &n, &k)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		sort(a, a+n, greater<int>());
		printf("%d\n", a[k-1]);
	}	
	return 0;
}

