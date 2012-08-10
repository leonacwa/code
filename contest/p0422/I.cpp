#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		long long n, ans, k;
		scanf("%lld", &n);
		if (n % 2 == 0) {
			k = n / 2;
			if ((k - 1) % 3 == 0) {
				ans = 2 * 81 * k % MOD * k % MOD * k % MOD * k % MOD;
			} else {
				ans = 2 * k % MOD * k % MOD * k % MOD * k % MOD;
			}
		} else {
			k = (n - 1) / 2;
			if ((k - 2) % 3 == 0) {
				ans = 2 * 81 * n % MOD * n % MOD * n % MOD * n % MOD;
			} else {
				ans = 2 * n % MOD * n % MOD * n % MOD * n % MOD;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}


