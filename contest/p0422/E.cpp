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
		int n;
		scanf("%d", &n);
		printf("%d", n);
		for (int i = n-1; i > 0; --i) {
			if (n % i == 0) {
				printf(" %d", i);
				n = i;
			}
		}
		puts("");
	}
	return 0;
}


