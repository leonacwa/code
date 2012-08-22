#include <stdio.h>
const int MOD = 100000000;
int n, m;
int f[13];
int cnt, st[1 << 12];
int cs[1 << 12];
int dp[13][1 << 12];

void init()
{
	cnt = 0;
	for (int s = (1 << n) - 1; s >= 0; --s) {
		int can = 1, t = s;
		while (t) {
			if ((t & 3) == 3) {
				can = 0;
				break;
			}
			t >>= 1;
		}
		if (can) {
			st[cnt++] = s;
		}
		cs[s] = can;
	}
}

int main()
{
	while (EOF != scanf("%d %d", &m, &n)) {
		for (int i = 0; i < m; ++i) {
			f[i] = 0;
			for (int j = n-1; j >= 0; --j) {
				int t;
				scanf("%d", &t);
				if (t == 0) {
					f[i] |= 1 << j;
				}
			}
		}
		init();
		for (int i = 0; i < cnt; ++i) {
			if (0 == (f[0] & st[i])) dp[0][st[i]] = 1;
		}
		for (int i = 1; i < m; ++i) {
			for (int j = 0; j < cnt; ++j) {
				if (dp[i-1][st[j]] == 0) continue;
				for (int k = 0; k < cnt; ++k) {
					if ((0 == (f[i] & st[k])) && (0 == (st[j] & st[k]))) {
						dp[i][st[k]] += dp[i-1][st[j]];
						dp[i][st[k]] %= MOD;
					}
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < cnt; ++i) {
			ans = (ans + dp[m-1][st[i]]) % MOD;
		}
		printf("%d\n", ans);
	}
	return 0;
}

