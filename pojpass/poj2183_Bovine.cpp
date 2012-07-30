#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int is[1000000];

int end6(int n) {
	int ret = 0, c = 6, b = 1;
	while (n && c > 0) {
		ret += n % 10 * b;
		b *= 10;
		n /= 10;
		--c;
	}
	return ret;
}

int mid4(int n) {
	return n / 10 % 10000;
}

int main()
{
	int n, nl, cnt;
	while (EOF != scanf("%d", &n)) {
		memset(is, 0, sizeof(is));
		cnt = 0;
		while (1) {
			++cnt;
			n = mid4(n);
			n = end6(n * n);
			if (is[n] > 0) {
				break;
			}
			is[n] = cnt;
		}
		printf("%d %d %d\n", n, cnt - is[n], cnt);
	}
	return 0;
}

