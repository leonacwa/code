#include <stdio.h>
#include <string.h>

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int y, m, d, h, mi, s;
		scanf("%d/%d/%d-%d:%d:%d", &y, &m, &d, &h, &mi, &s);
		printf("%02d/%02d/%4d-%02d:%02d:%02d%s\n", m, d, y, (h-1+12) % 12 + 1, mi, s, h<12?"am":"pm");
	}
	return 0;
}

