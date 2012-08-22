/* AC自动机 + 状态DP
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 128;
const int MAX_CHILD = 26;
const int MOD = 20090717;
char ch_num[128];
int num[(1<<10) + 10];

int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int ss[MAXN];

int f[26][MAXN][1<<10];

void insert(const char *s, int v) {
	int p = 0;
	for (; *s; ++s) {
		int i = ch_num[*s];
		if (nd[p][i] == 0) {
			memset(nd[nd_cnt], 0, sizeof(nd[nd_cnt]));
			fail[nd_cnt] = 0;
			ss[nd_cnt] = 0;
			nd[p][i] = nd_cnt++;
		}
		p = nd[p][i];
	}
	ss[p] = v;
}

int Q[MAXN];
void AC_construct()
{
	int *s = Q, *e = Q;
	for (int i = 0; i < MAX_CHILD; ++i) {
		if (nd[0][i]) {
			fail[nd[0][i]] = 0;
			*e++ = nd[0][i];
		}
	}
	while (s != e) {
		int q = *s++;
		for (int i = 0; i < MAX_CHILD; ++i) {
			if (nd[q][i]) {
				int v = nd[q][i];
				*e++ = v;
				fail[v] = nd[fail[q]][i];
				ss[v] |= ss[fail[v]];
			} else {
				nd[q][i] = nd[fail[q]][i];
			}
		}
	}
}


int main()
{
	for (int i = 0; i < MAX_CHILD; ++i) ch_num['a'+i] = i;
	num[0] = 0;
	for (int i = 1; i < 1<<10; ++i) num[i] = num[i>>1] + (i&1);
	int n, m, k;
	char str[32];
	while (EOF != scanf("%d%d%d", &n, &m, &k)) {
		if (n == 0 && m == 0 && k == 0) break;
		memset(nd[0], 0, sizeof(nd[0]));
		ss[0] = 0;
		fail[0] = 0;
		nd_cnt = 1;
		for (int i = 0; i < m; ++i) {
			scanf("%s", str);
			insert(str, 1<<i);
		}
		AC_construct();

		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j < nd_cnt; ++j) {
				for (int k = (1<<m) - 1; k >= 0; --k) {
					f[i][j][k] = 0;
				}
			}
		}
		f[0][0][0] = 1;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < nd_cnt; ++j) {
				for (int k = (1<<m) - 1; k >= 0; --k) {
					if (f[i][j][k] == 0) continue;
					for (int s = 0; s < MAX_CHILD; ++s) {
						int c = nd[j][s];
						f[i+1][c][k|ss[c]] += f[i][j][k];
						if (f[i+1][c][k|ss[c]] >= MOD) f[i+1][c][k|ss[c]] %= MOD;
					}
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < nd_cnt; ++i) {
			for (int j = (1<<m) - 1; j >= 0; --j) {
				if (num[j] < k) continue;
				ans += f[n][i][j];
				if (ans >= MOD) ans %= MOD;
			}
		}
		ans %= MOD;
		printf("%d\n", ans);
	}
	return 0;
}

