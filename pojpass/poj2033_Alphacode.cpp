#include <stdio.h>
#include <string.h>

const int MAXN = 1000000+5;

char s[MAXN];
int f[MAXN];

int main()
{
	while (EOF != scanf("%s", s) && strcmp(s, "0") != 0) {
		if (strlen(s) == 1) {
			puts("1");
		} else {
			f[0] = 1;
			int i, d = (s[0] - '0') * 10 + s[1] - '0';
			if (11 <= d && d <= 26 && d != 20) {
				f[1] = 2;
			} else {
				f[1] = 1;
			}
			for (i = 2; s[i]; i++) {
				d = (s[i-1] - '0') * 10 + s[i] - '0';
				if (d == 10 || d == 20) {
					f[i] = f[i-2];
				} else if (11 <= d && d <= 26 && d != 20) {
					f[i] = f[i-1] + f[i-2];
				} else {
					f[i] = f[i-1];
				}
			}
			printf("%d\n", f[i-1]);
		}
	}
	return 0;
}

