#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	char s[1024];
	while (gets(s)) {
		int sl = strlen(s);
		for (int i = 0; s[i]; i++) {
			s[i] = tolower(s[i]);
		}
		if (strstr(s, "qq") && strstr(s+sl-4, ".exe")) {
			puts("360 V5!");
		} else {
			puts("QQ 87!");
		}
	}
	return 0;
}

