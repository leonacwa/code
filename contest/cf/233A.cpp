/* A. Perfect Permutation
 * */
#include <cstdio>
#include <cstring>

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		if (n & 1) puts("-1");
		else {
			for (int i = 1; i <= n; i += 2) {
				printf(" %d %d", i+1, i);
			}
			printf("\n");
		}
	}
	return 0;
}
