/* 用AC自动机将字符串之间的可转移状态转换成图，建立邻接矩阵，使用矩阵乘法计算
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int64;

const int MAXN = 128;
const int MAX_CHILD = 4;
const int MOD = 100000;

int ch_num[128];
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int word[MAXN];
int matid[MAXN];
int nd_cnt;

void insert(const char *s, int v)
{
	int p = 0;
	for (; *s; ++s) {
		int i = ch_num[*s];
		if (nd[p][i] == 0) {
			memset(nd[nd_cnt], 0, sizeof(nd[nd_cnt]));
			fail[nd_cnt] = 0;
			word[nd_cnt] = 0;
			nd[p][i] = nd_cnt++;
		}
		p = nd[p][i];
	}
	word[p] |= v;
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
				word[v] |= word[fail[v]];
			} else {
				nd[q][i] = nd[fail[q]][i];
			}
		}
	}
}

void mat_mul(int l, int64 a[][MAXN], int64 b[][MAXN], int64 c[][MAXN])
{
	int mt[MAXN][MAXN];
	int64 Max = 0;
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
			mt[i][j] = 0;
			for (int k = 0; k < l; ++k) {
				mt[i][j] = (mt[i][j] + a[i][k] * b[k][j] % MOD) % MOD;
			}
			if (Max < mt[i][j]) Max = mt[i][j];
		}
	}
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
			c[i][j] = mt[i][j];
		}
	}
}

int64 mat[MAXN][MAXN];
int64 res[MAXN][MAXN];

int main()
{
	ch_num['A'] = 0;
	ch_num['C'] = 1;
	ch_num['T'] = 2;
	ch_num['G'] = 3;
	int n, m;
	while (EOF != scanf("%d%d", &m, &n)) {
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		word[0] = 0;
		nd_cnt = 1;
		char str[16];
		for (int i = 0; i < m; ++i) {
			scanf("%s", str);
			insert(str, 1<<i);
		}
		AC_construct();
		int matnum = 0;
		for (int i = 0; i < nd_cnt; ++i) {
			if (0 == word[i]) {
				matid[i] = matnum++;
			}
		}
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < nd_cnt; ++i) {
			if (word[i]) continue;
			for (int j = 0; j < MAX_CHILD; ++j) {
				if (word[nd[i][j]]) continue;
				mat[matid[i]][matid[nd[i][j]]]++;
			}
		}
		for (int i = 0; i < matnum; ++i) {
			res[i][i] = 1;
			for (int j = i+1; j < matnum; ++j) {
				res[i][j] = res[j][i] = 0;
			}
		}
		while (n) {
			if (n&1) mat_mul(matnum, res, mat, res);
			mat_mul(matnum, mat, mat, mat);
			n >>= 1;
		}
		int64 ans = 0;
		for (int i = 0; i < matnum; ++i) ans = (ans + res[0][i]) % MOD;
		printf("%lld\n", ans);
	}
	return 0;
}

