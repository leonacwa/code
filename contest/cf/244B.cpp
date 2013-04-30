/*
 * CF 244 B. Undoubtedly Lucky Numbers
 * */
#include <cstdlib>
#include <cstdio>
#include <cstring>

int c[12][12];

int main() {
	c[0][0] = 1;
	for (int i = 1; i <= 10; ++i) {
		c[i][0] = 1;
		c[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			c[i][j] = c[i-1][j] + c[i-1][j-1];
		}
	}
	char ns[32];
	scanf("%s", ns);
	int n = atoi(ns);
	int ans = 0;
	int ls = strlen(ns);
	if (ls == 1) {
		ans = ns[0] - '0';
	} else {
		ans += 9;
		for (int i = 2; i <= ls; ++i) {
			for (int a = 1; a <= 9; ++a) {
				long long d = 0;
				for (int j = 0; j < i; ++j) {
					d = d * 10 + a;
				}
				if (d <= n) ++ans;
				for (int b = 0; b <= 9; ++b) {
					if (a != b) {
						for (int s = (1<<(i-1))-1; s > 0; --s) {
							long long d = a;
							for (int j = 0; j < i-1; ++j) {
								d *= 10;
								if (s & (1<<j)) d += b;
								else d += a;
							}
							if (d <= n) {
								++ans;
							}
						}
					}
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
