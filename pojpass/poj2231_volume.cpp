#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 10000 + 5;
int n;
long long f, s;
int a[NN];

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a+1, a+n+1);
		f = s = 0;
		for (int i = 2; i <= n; ++i) {
			s += (i - 1) * (a[i] - a[i-1]);
			f += s;
		}
		f *= 2;
		printf("%lld\n", f);
	}
	return 0;
}

