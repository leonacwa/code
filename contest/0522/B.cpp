#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	int n, m;
	while (EOF != scanf("%d %d", &n, &m)) {
		if (m == 0) {
			printf("%d %d\n", n, n);
		} else if (n == 0) {
			puts("Impossible");
		} else if (n >= m) {
			printf("%d %d\n", n, n + m - 1);
		} else {
			printf("%d %d\n", m, n + m - 1);
		}
	}
	return 0;
}

