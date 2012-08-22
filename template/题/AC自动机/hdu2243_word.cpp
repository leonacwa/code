/* 用AC自动机将字符串之间的可转移状态转换成图，建立邻接矩阵，使用矩阵乘法计算
 * 幂的快速运算
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int64;
typedef unsigned long long uint64;

const int MAXN = 40;
const int MAX_CHILD = 26;

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

uint64 Pow(uint64 a, int n)
{
	uint64 s = 1;
	while (n) {
		if (n&1) s *= a;
		a *= a;
		n >>= 1;
	}
	return s;
}

uint64 Sum(uint64 a, int n)
{
	if (n == 1) return a;
	uint64 s = Sum(a, n>>1) * (1 + Pow(a, n>>1));
	if (n & 1) s += Pow(a, n);
	return s;
}

void MatAdd(int l, uint64 a[][MAXN], uint64 b[][MAXN])
{
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
			a[i][j] += b[i][j];
		}
	}
}

void MatMul(int l, uint64 a[][MAXN], uint64 b[][MAXN], uint64 c[][MAXN])
{
	uint64 mt[MAXN][MAXN];
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
			mt[i][j] = 0;
			for (int k = 0; k < l; ++k) {
				mt[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
			c[i][j] = mt[i][j];
		}
	}
}

void MatPow(int l, uint64 a[][MAXN], int n, uint64 b[][MAXN])
{
	uint64 A[MAXN][MAXN];
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < l; ++j) {
		  	A[i][j] = a[i][j];
			b[i][j] = 0;
		}
		b[i][i] = 1;
	}
	while (n) {
		if (n&1) MatMul(l, A, b, b);
		MatMul(l, A, A, A);
		n >>= 1;
	}
}

void MatSum(int l, uint64 a[][MAXN], int n, uint64 b[][MAXN])
{
	if (n == 1) {
		for (int i = 0; i < l; ++i) {
			for (int j = 0; j < l; ++j) {
				b[i][j] = a[i][j];
			}
		}
		return;
	}
	uint64 A[MAXN][MAXN];
	uint64 B[MAXN][MAXN];
	uint64 C[MAXN][MAXN];
	MatSum(l, a, n>>1, A);
	MatPow(l, a, n>>1, B);
	for (int i = 0; i < l; ++i) B[i][i]++;
	if (n&1) {
		MatPow(l, a, n, C);
		MatMul(l, A, B, b);
		MatAdd(l, b, C);
	} else {
		MatMul(l, A, B, b);
	}
}

uint64 mat[MAXN][MAXN];
uint64 res[MAXN][MAXN];

int main()
{
	for (int i = 0; i < 26; ++i) ch_num['a'+i] = i;
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
		int64 ans = Sum(26, n);
		MatSum(matnum, mat, n, res);
		for (int i = 0; i < matnum; ++i) {
			ans = ans - res[0][i];
		}
		printf("%llu\n", ans);
		//printf("%I64u\n", ans);
	}
	return 0;
}

