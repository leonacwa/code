/* ZOJ 3662 Math Magic
 * 要分类的话，就是状态DP吧
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 1005;
const int MOD = 1000000007;

struct DS {
	int d, s;
} ds[MAXN];

int dp[102][16][MAXN];
int p[MAXN];

bool is[MAXN];
int prm[MAXN];
int prm_cnt;

void get_prm() {
	memset(is, 1, sizeof(is));
	is[0] = is[1] = false;
	for (int i = 2; i < MAXN; ++i) {
		if (is[i]) {
			for (int j = i + i; j < MAXN; j += i) is[j] = false;
		}
	}
	prm_cnt = 0;
	for (int i = 2; i < MAXN; ++i) {
		if (is[i]) prm[prm_cnt++] = i;
	}
}

int main() {
	get_prm();
	int n, m, k;
	while (EOF != scanf("%d%d%d", &n, &m, &k)) {
		int np = 0;
		int t = m;
		for (int i = 0; i < prm_cnt && prm[i] <= t; ++i) {
			if (t % prm[i] == 0) {
				p[np] = 1;
				while (t % prm[i] == 0) {
					p[np] *= prm[i];
					t /= prm[i];
				}
				++np;
			}
		}
		int nds = 0;
		for (int i = 1; i <= m; ++i) {
			if (m % i == 0) {
				ds[nds].d = i;
				ds[nds].s = 0;
				for (int j = 0; j < np; ++j) {
					if (i % p[j] == 0) ds[nds].s |= 1 << j;
				}
				++nds;
			}
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0][0] = 1;
		for (int i = 0; i < k; ++i) {
			for (int s = (1<<np)-1; s >= 0; --s) {
				for (int j = 0; j < n; ++j) {
					if (dp[i][s][j] == 0) continue;
					for (int a = 0; a < nds && j + ds[a].d <= n; ++a) {
						int s2 = s | ds[a].s, sum = j + ds[a].d;
						dp[i+1][s2][sum] += dp[i][s][j];
						if (dp[i+1][s2][sum] >= MOD) dp[i+1][s2][sum] -= MOD;
					}
				}
			}
		}
		printf("%d\n", dp[k][(1<<np)-1][n]);
	}
	return 0;
}
