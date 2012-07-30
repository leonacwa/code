#include <cstdio>
#include <cstring>

typedef unsigned int uint;
uint y, a, b, c, n, n2;

bool f(uint x) {
	uint z = (a * x * x + b * x + c) % n2;
	return z == y % n2;
}

int main()
{
	int runs;
	scanf("%d", &runs);
	while (EOF != scanf("%d%d%d%d%d", &y, &a, &b, &c, &n)) {
		bool ans = true;
		uint x = 0;
		n2 = 1;
		for (int i = 1; i <= n; ++i) {
			n2 <<= 1;
			if (n2 <= 0) puts("error");
			bool f1 = f(x), f2 = f(x + (n2>>1));
			if (!f1 && f2) x += (n2 >> 1);
			if (f1 == f2) {
				ans = false;
				break;
			}
		}
		if (!ans) puts("No unique solution");
		else printf("%d\n", x);
	}
	return 0;
}
