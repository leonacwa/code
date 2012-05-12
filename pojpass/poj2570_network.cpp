#include <cstdio>
#include <cstring>
const int MAXN = 201;
int mat[MAXN][MAXN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n) && n > 0) {
		memset(mat, 0, sizeof(mat));
		int a, b;
		char s[32];
		while (EOF != scanf("%d %d", &a, &b) && a > 0 && b > 0) {
			scanf("%s", s);
			for (char *c = s; *c; ++c) {
				mat[a][b] |= 1 << (*c - 'a');
			}
		}
		for (int k = 1; k <= n; ++k) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					mat[i][j] |= mat[i][k] & mat[k][j];
				}
			}
		}
		while (EOF != scanf("%d %d", &a, &b) && a > 0 && b > 0) {
			if (mat[a][b] == 0) {
				putchar('-');
			} else {
				for (int i = 0; i < 26; ++i) {
					if (mat[a][b] & (1 << i)) {
						putchar('a' + i);
					}
				}
			}
			putchar('\n');
		}
		putchar('\n');
	}
	return 0;
}

