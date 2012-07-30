/* AC自动机 + 状态DP
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 505;
const int MAX_CHILD = 4;
const int MAXS = 11 * 11 * 11 * 11;
char ch_num[128];

int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int ss[MAXN];

int f[MAXS][MAXN];
char str[64];
int cnt[MAX_CHILD];
int hash[MAX_CHILD+1];
int DNA[MAX_CHILD];

void insert(const char *s) {
	int p = 0;
	for (; *s; ++s) {
		int i = ch_num[*s];
		if (nd[p][i] == 0) {
			nd[nd_cnt][0] = nd[nd_cnt][1] = nd[nd_cnt][2] = nd[nd_cnt][3] = 0;
			fail[nd_cnt] = 0;
			ss[nd_cnt] = 0;
			nd[p][i] = nd_cnt++;
		}
		p = nd[p][i];
	}
	ss[p]++;
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
				ss[v] += ss[fail[v]];
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
		nd[0][0] = nd[0][1] = nd[0][2] = nd[0][3] = 0;
		fail[0] = 0;
		ss[0] = 0;
		nd_cnt = 1;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str);
			insert(str);
		}
		AC_construct();

		scanf("%s", str);
		cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
		for (int i = 0; str[i]; ++i) {
			cnt[ch_num[str[i]]]++;
		}
		hash[0] = 1;
		for (int i = 1; i <= MAX_CHILD; ++i) {
			hash[i] = hash[i-1] * (1 + cnt[i-1]);
		}
		int total = hash[MAX_CHILD];
		memset(f, -1, sizeof(f));
		f[0][0] = 0;
		int ans = 0;
		for (int i = 0; i < total; ++i) {
			DNA[0] = i % hash[1] / hash[0];
			DNA[1] = i % hash[2] / hash[1];
			DNA[2] = i % hash[3] / hash[2];
			DNA[3] = i % hash[4] / hash[3];
			if (DNA[0] > cnt[0] || DNA[1] > cnt[1] || DNA[2] > cnt[2] || DNA[3] > cnt[3]) continue;
			for (int j = 0; j < nd_cnt; ++j) if (f[i][j] != -1) {
				int is, c, t;
				if (DNA[0]<cnt[0] && (is=i+hash[0]) < total && f[is][c=nd[j][0]] < (t=f[i][j]+ss[c])) f[is][c] = t;
				if (DNA[1]<cnt[1] && (is=i+hash[1]) < total && f[is][c=nd[j][1]] < (t=f[i][j]+ss[c])) f[is][c] = t;
				if (DNA[2]<cnt[2] && (is=i+hash[2]) < total && f[is][c=nd[j][2]] < (t=f[i][j]+ss[c])) f[is][c] = t;
				if (DNA[3]<cnt[3] && (is=i+hash[3]) < total && f[is][c=nd[j][3]] < (t=f[i][j]+ss[c])) f[is][c] = t;
			}
		}
		for (int i = 0; i < nd_cnt; ++i) if (ans < f[total-1][i]) ans = f[total-1][i];
		printf("Case %d: %d\n", ++nCase, ans);
	}
	return 0;
}

