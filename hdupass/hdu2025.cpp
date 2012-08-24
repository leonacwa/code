#include <stdio.h>
#include <string.h>

int main()
{
	char s[128], c;
	int i;
	while (gets(s)) {
		c = 0;
		for (i = 0; s[i]; ++i) {
			if (s[i] > c)
				c = s[i];
		}
		for (i = 0; s[i]; ++i) {
			putchar(s[i]);
			if (s[i] == c)
				printf("(max)");
		}
		puts("");
	}
	return 0;
}
