#include <cstdio>
#include <cstring>

int main()
{
	int a, b;
	char s[256];
	while (EOF != scanf("%d %s", &a, s)) {
		int l = strlen(s);
		b = 0;
		for (int i = l -1; i >= 0; --i) {
			b = b * 10 + s[i] - '0';
		}
		printf("%d\n", a + b);
	}
	return 0;
}

