#include <stdio.h>

int main()
{
	char s[2024];
	int T;
	int ch, ans;
	while (~scanf("%d\n", &T) && T > 0) {

		while (T--) {
			gets(s);
			int c[256] ={0};
			for (int i = 0; s[i]; i++) {
				c[s[i]]++;
			}
			ans = 'a';
			for (ch = 'a'; ch <= 'z'; ch++) {
				if (c[ch] > c[ans]) {
					ans = ch;
				}
			}
			printf("%c\n", ans);
		}
	}
	return 0;
}

