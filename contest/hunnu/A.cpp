#include <stdio.h>
#include <string.h>

int main()
{
	char s[10];
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%s", s);
		char b = 0;
		for (int i = 1; i < 8; ++i) {
			if (s[i] == '1') {
				b |= 1 << (7 - i);
			}
		}
		if (s[0] == '1') {
			b = (~b & ((1 << 7) - 1)) + 1;
			b |= (1 << 7);
		}
		for (int i = 7; i >= 0; --i) {
			printf("%d", (b&(1<<i)) ? 1 : 0);
		}
		printf("\n");
	}
	return 0;
}

