#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

void get(int n, int &a, int &b)
{
	int end = ((int)sqrt(n)) + 1;
	for (int i = 2; i <= end; ++i) {
		if ((n % i == 0) && (i <= n / i)) {
			a = i;
			b = n / i;
			return;
		}
	}
	a = 1;
	b = n;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, a, b;
		scanf("%d", &n);
		get(n, a, b);
		int at = 1;
		while (a > 1 && at < n) {
			at *= a;
		}
		if ((at == n) || (a == 1)) {
			puts("NO");
		} else {
			puts("YES");
		}
	}
	return 0;
}

