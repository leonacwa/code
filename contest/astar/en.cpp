#include <cstdio>
#include <cstring>

char str[2048];
int num[256];

int main()
{
	for (char c = '0'; c <= '9'; ++c) {
		num[c] = c - '0';
	}
	for (char c = 'A'; c <= 'F'; ++c) {
		num[c] = c - 'A' + 10;
	}
	printf("%x  %x\n", '#', '#' - 0x17);
	printf("%x  %x\n", 'i', 'i' - 0x6d);
	printf("%x  %x\n", '<', '>');
	while (EOF != scanf("%s", str)) {
		int l = strlen(str);
		for (int i = 0; i < l; i += 2) {
			putchar(num[str[i]] * 16 + num[str[i+1]]);
		}
		puts("");
	}
	return 0;
}

