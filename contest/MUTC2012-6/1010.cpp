/* Easy Tree DP?
 * */
#include <cstdio>
#include <cstring>

typedef long long int64;

const int MOD = 1000000000 + 7;
const int MAXN = 361;

int64 c[MAXN][MAXN];
int64 fl[MAXN][MAXN], fe[MAXN][MAXN];

void _MOD(int64 &a) {
	if (a >= MOD) a %= MOD;
	else if (a < 0) a = (a + MOD) % MOD;
}

int64 FL(int n, int d) {
	if (n == 0) {
		if (d >= 0) return 1;
		return 0;
	}
	if (d < 0 || n < 0) return 0;
	if (n == 1) {
		if (d >= 1) return 1;
		return 0;
	}
	if (fl[n][d] != -1) return fl[n][d];
	int64 ret = 0, t;
	for (int i = 0; i < n; ++i) {
		t = FL(i, d-1) * FL(n-1-i, d-1) % MOD;
		_MOD(t);
		if (i < n-1 && c[n-2][i] > 0) t *= c[n-2][i];
		ret += t;
		_MOD(ret);
	}
	ret *= n;
	_MOD(ret);
	return fl[n][d] = ret;
}

int64 FE(int n, int d) {
	if (n == 0) {
		if (d == 0) return 1;
		return 0;
	}
	if (d < 0 || n < d || n < 0) return 0;
	if (n == 1) {
		if (d == 1) return 1;
		return 0;
	}
	if (fe[n][d] != -1) return fe[n][d];
	int64 ret = 0, t;
	for (int i = 0; i < n; ++i) {
		t = FE(i, d-1) * FL(n-1-i, d-1) % MOD + 
			FL(i, d-1) * FE(n-1-i, d-1) % MOD - 
			FE(i, d-1) * FE(n-1-i, d-1) % MOD;
		_MOD(t);
		if (i < n-1 && c[n-2][i] > 0) t *= c[n-2][i];
		_MOD(t);
		ret += t;
		_MOD(ret);
	}
	ret *= n;
	_MOD(ret);
	return fe[n][d] = ret;
}

int main() {
	memset(c, 0, sizeof(c));
	c[0][0] = 1;
	for (int i = 1; i < MAXN; ++i) c[i][0] = c[i][i] = 1;
	for (int i = 1; i < MAXN; ++i) {
		for (int j = 1; j < i; ++j) {
			c[i][j] = c[i-1][j] + c[i-1][j-1];
			if (c[i][j] >= MOD) c[i][j] %= MOD;
		}
	}
	int runs;
	scanf("%d", &runs);
	memset(fl, -1, sizeof(fl));
	memset(fe, -1, sizeof(fe));
	FE(360, 360);
	for (int run = 1; run <= runs; ++run) {
		int n, d;
		scanf("%d%d", &n, &d);
		printf("Case #%d: %lld\n", run, FE(n, d));
	}
	return 0;
}
