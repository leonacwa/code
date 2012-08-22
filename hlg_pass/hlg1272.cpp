#include <stdio.h>
int main()
{
	char f[1024];
	int i;
	while (gets(f)) {
		for (i = 0; f[i] != '.' && f[i]; i++) ;
		f[i+3] = 0;
		puts(f);
	}
	return 0;
}

