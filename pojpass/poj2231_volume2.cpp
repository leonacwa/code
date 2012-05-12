#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 10000 + 5;
int n;
long long f;
long long a[NN];

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}
		sort(a+1, a+n+1);
		f = 0;
		for (int i = 1; i < n; ++i) {
			f += (a[i+1] - a[i]) * i * (n - i);
		}
		f *= 2;
		printf("%lld\n", f);
	}
	return 0;
}

