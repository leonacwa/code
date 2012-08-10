/* AC自动机 + 状态DP
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
const int MAX_CHILD = 4;
char ch_num[128];

int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int ss[MAXN];

int f[1024][MAXN];
char str[1024];

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
	ch_num['A'] = 0;
	ch_num['G'] = 1;
	ch_num['C'] = 2;
	ch_num['T'] = 3;
	int nCase = 0, n;
	while (EOF != scanf("%d", &n) && n != 0) {
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		ss[0] = 0;
		nd_cnt = 1;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str);
			insert(str, 1);
		}
		scanf("%s", str);
		AC_construct();
		int len = strlen(str);
		for (int i = 0; i <= len; ++i) {
			for (int j = 0; j < nd_cnt; ++j) {
				f[i][j] = -1;
			}
		}
		f[0][0] = 0;
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < nd_cnt; ++j) {
				if (f[i][j] == -1) continue;
				for (int s = 0; s < MAX_CHILD; ++s) {
					int c = nd[j][s];
					if (ss[c]) continue;
					if (f[i+1][c] == - 1 || f[i+1][c] > f[i][j] + (ch_num[str[i]] != s)) {
						f[i+1][c] = f[i][j] + (ch_num[str[i]] != s);
					}
				}
			}
		}
		int ans = -1;
		for (int i = 0; i < nd_cnt; ++i) {
			if (f[len][i] != -1 && (ans == -1 || ans > f[len][i])) {
				ans = f[len][i];
			}
		}
		printf("Case %d: %d\n", ++nCase, ans);
	}
	return 0;
}

