#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 1001;
const int _MOD = 1000000007;
int C[NN][NN];

int main()
{
	memset(C, 0, sizeof(C));
	C[0][0] = 1;
	for (int i = 1; i <= NN; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= NN; ++j) {
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % _MOD;
		}
	}
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int r, c, k;
		scanf("%d %d %d", &r, &c, &k);
		long long ans;
		if (r-1 < 2*k || c-1 < 2*k) {
			ans = 0;
		} else {
			ans	= C[r-1][2*k];
			ans *= C[c-1][2*k];
			ans %= _MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

