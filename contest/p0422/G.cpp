#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int a[1000+5];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, k;
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}
		while (k--) {
			if (!next_permutation(a, a + n)) {
			}
		}
		printf("%d", a[0]);
		for (int i = 1; i < n; ++i) {
			printf(" %d", a[i]);
		}
		puts("");
	}
	return 0;
}


