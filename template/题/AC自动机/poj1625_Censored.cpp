/* AC自动机 + DP + 大数
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 512;
const int MAX_CHILD = 50;
struct Integer {
	int l;
	int a[100];
	void clear() {
		memset(a, 0, sizeof(a));
		l = 1;
	}
};

int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int word[MAXN];
int matid[MAXN];
int nd_cnt, CHAR_SET;
char ch_num[128];
int mat[MAXN][MAXN];
Integer f[60][MAXN];

void insert(const char *s, int v)
{
	int i, p = 0;
	for (; *s; ++s) {
		i = ch_num[*s];
		if (nd[p][i] == 0) {
			memset(nd[nd_cnt], 0, sizeof(nd[nd_cnt]));
			fail[nd_cnt] = 0;
			word[nd_cnt] = 0;
			nd[p][i] = nd_cnt++;
		}
		p = nd[p][i];
	}
	word[p] = v;
}

int Q[MAXN];
void AC_construct()
{
	int *s = Q, *e = Q;
	for (int i = 0; i < CHAR_SET; ++i) {
		if (nd[0][i]) {
			fail[nd[0][i]] = 0;
			*e++ = nd[0][i];
		}
	}
	while (s != e) {
		int q = *s++;
		for (int i = 0; i < CHAR_SET; ++i) {
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

void init_mat(int mat[][MAXN], int &l)
{
	l = 0;
	for (int i = 0; i < nd_cnt; ++i) {
		if (word[i]) continue;
		matid[i] = l++;
	}
	memset(mat, 0, sizeof(int)*MAXN*MAXN);
	for (int i = 0; i < nd_cnt; ++i) {
		if (word[i]) continue;
		for (int j = 0; j < CHAR_SET; ++j) {
			if (word[nd[i][j]]) continue;
			mat[matid[i]][matid[nd[i][j]]]++;
		}
	}
}

void Add(Integer &a, Integer &b)
{
	for (int i = 0; i < b.l; ++i) {
		if (i < a.l) {
			a.a[i] += b.a[i];
		} else {
			a.a[i] = b.a[i];
		}
	}
	if (a.l < b.l) a.l = b.l;
	for (int i = 0; i < a.l; ++i) {
		if (a.a[i] >= 10) {
			a.a[i+1] += a.a[i] / 10;
			a.a[i] %= 10;
		}
	}
	while (a.a[a.l] >= 10) {
		a.a[a.l+1] += a.a[a.l] / 10;
		a.a[a.l] %= 10;
		a.l++;
	}
	if (a.a[a.l] > 0) a.l++;
}

void Mul(Integer &a, int n, Integer &b)
{
	if (&a == &b) puts("error");
	b.clear();
	if (a.l == 0 || n == 0 || (a.l == 1 && a.a[0] == 0)) {
		return;
	}
	for (int i = 0; i < a.l; ++i) b.a[i] = a.a[i] * n;
	for (int i = 0; i < a.l; ++i) {
		if (b.a[i] >= 10) {
			b.a[i+1] += b.a[i] / 10;
			b.a[i] %= 10;
		}
	}
	b.l = a.l;
	while (b.a[b.l] >= 10) {
		b.a[b.l+1] = b.a[b.l] / 10;
		b.a[b.l] %= 10;
		b.l++;
	}
	if (b.a[b.l] > 0) ++b.l;
}

void Print(const Integer &a) {
	for (int i = a.l - 1; i >= 0; --i) printf("%d", a.a[i]);
}

int main()
{
	int n, m, p;
	while (EOF != scanf("%d%d%d", &n, &m, &p)) {
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		word[0] = 0;
		nd_cnt = 1;
		char str[64];
		gets(str);
		gets(str);
		//scanf("%s", str);
		for (int i = 0; i < n; ++i) ch_num[str[i]] = i;
		CHAR_SET = n;
		for (int i = 0; i < p; ++i) {
			scanf("%s", str);
			insert(str, 1);
		}
		AC_construct();
		int l;
		init_mat(mat, l);
		for (int i = 0; i < l; ++i) {
			f[0][i].clear();
		}
		f[0][0].a[0] = 1;
		f[0][0].l = 1;
		Integer ans;
		for (int k = 1; k <= m; ++k) {
			for (int i = 0; i < l; ++i) {
				f[k][i].clear();
				for (int j = 0; j < l; ++j) {
					Mul(f[k-1][j], mat[j][i], ans);
					Add(f[k][i], ans);
					/*
					Print(f[k-1][j]);
					printf(" * %d = ", mat[j][i]);
					Print(ans);
					puts("");
					*/
				}
			}
		}
		ans.clear();
		for (int i = 0; i < l; ++i) {
			Add(ans, f[m][i]);
		}
		Print(ans);
		printf("\n");
	}
	return 0;
}

