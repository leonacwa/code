#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n;
		scanf("%d", &n);
		int x = -1, y = -1;
		for (x = 0; 4 * x <= n; ++x) {
			if ((n - 4 * x) % 7 == 0) {
				y = (n - 4 * x) / 7;
				break;
			}
		}
		if (y == -1) {
			puts("-1");
		} else {
			for (int i = 0; i < x; ++i) {
				printf("4");
			}
			for (int i = 0; i < y; ++i) {
				printf("7");
			}
			puts("");
		}
	}
	return 0;
}

