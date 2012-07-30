/*
 * http://zerojudge.tw/ShowProblem?problemid=b179
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1500 + 100;
const int MAX_CHILD = 4;
const int MOD = 10007;
char ch_num[128];

int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int len[MAXN];
int ss[MAXN];

int f[2][101][MAXN];

char str[256];
char dna[256];

void insert(const char *s) {
	int p = 0;
	for (; *s; ++s) {
		int i = ch_num[*s];
		if (nd[p][i] == 0) {
			memset(nd[nd_cnt], 0, sizeof(nd[nd_cnt]));
			fail[nd_cnt] = 0;
			ss[nd_cnt] = 0;
			len[nd_cnt] = len[p] + 1;
			nd[p][i] = nd_cnt++;
		}
		p = nd[p][i];
	}
	ss[p] = 1;
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
				int t = fail[q];
				while (nd[t][i] == 0 && t != 0) t = fail[t];
				fail[v] = nd[t][i];
				ss[v] |= ss[fail[v]];
			} else {
				nd[q][i] = nd[fail[q]][i];
			}
		}
	}
}

int AC_find(const char *s)
{
	int p = 0, q, i;
	for (; *s; ++s) {
		i = ch_num[*s];
		q = p = nd[p][i];
		while (q != 0 && ss[q] == 0) {
			q = fail[q];
		}
		if (ss[q]) return -1;
	}
	return p;
}

int main()
{
	for (int i = 0; i < MAX_CHILD; ++i) ch_num['a'+i] = i;
	int n, p;
	while (EOF != scanf("%s%d%d", str, &p, &n)) {
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		ss[0] = 0;
		len[0] = 0;
		nd_cnt = 1;
		for (int i = 0; i < n; ++i) {
			scanf("%s", dna);
			insert(dna);
		}
		AC_construct();

		memset(f, 0, sizeof(f));
		int s = AC_find(str);
		if (-1 == s) {
			puts("0 1");
			continue;
		}
		int recyle = 0, hospital = 0;
		f[0][strlen(str)][s] = 1;
		int now = 0;
		while (p--) {
			now = 1 - now;
			memset(f[now], 0, sizeof(f[now]));
			for (int i = 0; i < nd_cnt; ++i) {
				if (ss[i]) continue;
				for (int j = 1; j <= 100; ++j) if (f[1-now][j][i]) {
					if (j == 1) {
						recyle = (recyle + f[1-now][j][i]) % MOD;
					} else if (len[i] > j-1) {
						int t = fail[i];
						f[now][j-1][t] = (f[now][j-1][t] + f[1-now][j][i]) % MOD;
					} else {
						f[now][j-1][i] = (f[now][j-1][i] + f[1-now][j][i]) % MOD;
					}
					for (int s = 0; s < MAX_CHILD; ++s) {
						int is = nd[i][s];
						f[now][j+1][is] = (f[now][j+1][is] + f[1-now][j][i]) % MOD;
					}
				}
			}
			for (int i = 0; i < nd_cnt; ++i) {
				if (ss[i] == 0) continue;
				for (int j = 1; j <= 100; ++j) if (f[now][j][i]) {
					hospital = (hospital + f[now][j][i]) % MOD;
				}
			}
		}
		printf("%d %d\n", recyle, hospital);
	}
	return 0;
}

