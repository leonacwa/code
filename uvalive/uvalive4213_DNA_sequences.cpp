/* DNA Sequences [South American Regional 2008]
 * 动态规划，但是不理解题意
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 1005;

int f[MAXN][MAXN], g[MAXN][MAXN];
char s[MAXN], w[MAXN];

int max(int a, int b) {
	return a > b? a : b;
}

int main() {
	int k;
	while (EOF != scanf("%d", &k)) {
		if (k == 0) break;
		scanf("%s%s", s+1, w+1);
		int ls = strlen(s+1), lw = strlen(w+1);
		for (int i = 1; i <= ls; ++i) {
			for (int j = 1; j <= lw; ++j) {
				if (s[i] == w[j]) {
					g[i][j] = g[i-1][j-1] + 1;
				} else {
					g[i][j] = 0;
				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= ls; ++i) {
			for (int j = 1; j <= lw; ++j) {
				f[i][j] = max(f[i-1][j], f[i][j-1]);
				for (int r = k; r <= g[i][j]; ++r) {
					f[i][j] = max(f[i][j], f[i-r][j-r] + r);
				}
			}
		}
		printf("%d\n", f[ls][lw]);
	}
	return 0;
}
