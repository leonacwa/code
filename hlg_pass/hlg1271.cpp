#include <stdio.h>
#include <string.h>

int main()
{
	char s[1024];
	while (gets(s)) {
		for (int i = 0;  s[i]; i++) {
			s[i] = '*';
		}
		puts(s);
	}
	return 0;
}

