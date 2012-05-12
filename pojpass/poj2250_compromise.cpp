#include <stdio.h>
#include <string.h>

char sa[105][32], sb[105][32];
int a_cnt, b_cnt;
char txt[105][32];
int f[105][105], opt[105][105];

int main()
{
	a_cnt = 0;
	while (EOF != scanf("%s", sa[1])) {
		a_cnt = 1;
		while (scanf("%s", sa[a_cnt+1])) {
			if (sa[a_cnt+1][0] == '#') break;
			++a_cnt;
		}
		b_cnt = 0;
		while (scanf("%s", sb[b_cnt+1])) {
			if (sb[b_cnt+1][0] == '#') break;
			++b_cnt;
		}
		for (int i = 0; i <= a_cnt; ++i) {
			f[i][0] = 0;
			opt[i][0] = 0;
		}
		for (int i = 0; i <= b_cnt; ++i) {
			f[0][i] = 0;
			opt[0][i] = 0;
		}
		for (int i = 1; i <= a_cnt; ++i) {
			for (int j = 1; j <= b_cnt; ++j) {
				f[i][j] = 0;
				if (0 == strcmp(sa[i], sb[j])) {
					f[i][j] = f[i-1][j-1] + 1;
					opt[i][j] = 1;
				}
				if (f[i][j] < f[i-1][j]) {
					f[i][j] = f[i-1][j];
					opt[i][j] = 2;
				}
				if (f[i][j] < f[i][j-1]) {
					f[i][j] = f[i][j-1];
					opt[i][j] = 3;
				}
			}
		}
		int cnt = 0, a = a_cnt, b = b_cnt;
		while (cnt < f[a_cnt][b_cnt]) {
			if (opt[a][b] == 1) {
				strcpy(txt[cnt], sa[a]);
				++cnt;
				--a, --b;
			} else if (opt[a][b] == 2) {
				--a;
			} else if (opt[a][b] == 3) {
				--b;
			}
		}
		for (int i = cnt - 1; i > 0; --i) {
			printf("%s ", txt[i]);
		}
		printf("%s\n", txt[0]);
		a_cnt = 0;
	}
	return 0;
}

