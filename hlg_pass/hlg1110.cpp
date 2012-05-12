#include <stdio.h>
#include <string.h>
char str[4096];
int main()
{
	while (gets(str)) {
		printf("%d\n", strlen(str));
	}
	return 0;
}

