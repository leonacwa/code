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

int n, m, k, np, nds;

int dfs(int i, int s, int j) {
	int &now = dp[i][s][j];
	if (now != -1) return now;
	if (i == 0 || j == 0) return 0;
	now = 0;
	for (int a = 0; a < nds && ds[a].d <= j; ++a) {
		if ((s|ds[a].s) != s) continue;
		if (ds[a].s) {
			for (int s2 = ds[a].s; s2 > 0; -- s2) { // 记忆化搜索时，要把状态转移数算够了
				if (ds[a].s != (ds[a].s | s2)) continue;
				now += dfs(i-1, s^s2, j - ds[a].d);
				if (now >= MOD) now -= MOD;
			}
		}
		now += dfs(i-1, s, j - ds[a].d);
		if (now >= MOD) now -= MOD;
	}
	return now;
}

int main() {
	get_prm();
	while (EOF != scanf("%d%d%d", &n, &m, &k)) {
		np = 0;
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
		nds = 0;
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
		memset(dp, -1, sizeof(dp));
		dp[0][0][0] = 1;
		printf("%d\n", dfs(k, (1<<np)-1, n));
	}
	return 0;
}
