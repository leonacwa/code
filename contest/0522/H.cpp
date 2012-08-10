#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long llong;
typedef llong INT[2][2];
const llong MOD = 1000000007;

void mul(INT a, INT b, INT c)
{
	INT t;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			t[i][j] = 0;
			for (int k = 0; k < 2; ++k) {
				t[i][j] += a[i][k] * b[k][j] % MOD;
				t[i][j] %= MOD;
			}
		}
	}
	memcpy(c, t, sizeof(INT));
}

int main()
{
	llong n;
	while (EOF != scanf("%lld", &n)) {
		if (n == 0) {
			puts("1");
		} else {
			INT a = {{3, 1}, {1, 3}}, b = {{1, 0}, {0, 1}};
			while (n) {
				if (n & 1) {
					mul(b, a, b);
				}
				mul(a, a, a);
				n >>= 1;
			}
			printf("%lld\n", b[0][0] % MOD);
		}
	}
	return 0;
}

