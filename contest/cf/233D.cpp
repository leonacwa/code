/* D. Table
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long int64;
const int64 MOD = 1000000007;

int64 c[101][101];
int cnt[101];
int64 dp[101][10005];

int64  q0[101], q1[101];

int64 qpow(int64 a, int64 n) {
	if (n == 0) return 1;
	if (n == 1) return a;
	int64 r = qpow(a, n >> 1) % MOD;
	r = (r * r) % MOD;
	if (n & 1) r = (r * a) % MOD;
	return r;
}

int main() {
	memset(c, 0, sizeof(c));
	c[0][0] = 1;
	for (int i = 1; i <= 100; ++i) {
		c[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
		}
	}
	int64 n, m, k, m_n, mn;
	cin >> n >> m >> k;
	m_n = m / n;
	mn = m % n;
	for (int i = 0; i <= n; ++i) {
		q0[i] = qpow(c[n][i], m_n);
		q1[i] = qpow(c[n][i], m_n+1);
	}
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 0; i < n; ++i) {
		int64* qw = (i < mn ? q1 : q0);
		for (int j = 0; j <= k; ++j) {
			if (dp[i][j] == 0) continue;
			for (int q = 0; j+q <= k && q <= n; ++q) {
				dp[i+1][j+q] += dp[i][j] * qw[q] % MOD;
				if (dp[i+1][j+q] >= MOD) dp[i+1][j+q] -= MOD;
			}
		}
	}
	cout << dp[n][k] << endl;
	return 0;
}
