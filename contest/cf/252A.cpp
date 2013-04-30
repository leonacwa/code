/*
 * CF 252 A. Little Xor
 * */
#include <cstdio>
#include <cstring>

int a[105];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	int s = 0;
	for (int i = 0; i < n; ++i) {
		int t = 0;
		for (int j = i; j < n; ++j) {
			t ^= a[j];
			if (s < t) s = t;
		}
	}
	printf("%d\n", s);
	return 0;
}
