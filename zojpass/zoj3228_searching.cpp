/* AC自动机
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

const int MAX_LEN = 100000 + 10;
const int MAXN = MAX_LEN * 6;
const int MAX_CHILD = 26;
char ch_num[128];
// AC data structure
int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int id[MAXN];

// problem data
int len[MAX_LEN];
int over[MAX_LEN];
int n_over[MAX_LEN];
int last_pos[MAX_LEN];

char str[MAX_LEN];

struct Query {
	int d;
	char word[8];
} qry[MAX_LEN];

int ID;
int insert(const char *s) {
	int p = 0;
	for (; *s; ++s) {
		int i = ch_num[*s];
		if (nd[p][i] == 0) {
			memset(nd[nd_cnt], 0, sizeof(nd[nd_cnt]));
			fail[nd_cnt] = 0;
			id[nd_cnt] = 0;
			nd[p][i] = nd_cnt++;
		}
		p = nd[p][i];
	}
	if (id[p] == 0) id[p] = ++ID;
	return id[p];
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
				//ss[v] += ss[fail[v]];
			} else {
				nd[q][i] = nd[fail[q]][i];
			}
		}
	}
}

void AC_find(const char *s)
{
	int p = 0, q, i;
	for (int l = 0; s[l]; ++l) {
		i = ch_num[s[l]];
		while (p != 0 && nd[p][i] == 0) p = fail[p];
		q = p = nd[p][i];
		for (; q != 0; q = fail[q]) {
			if (id[q] == 0) continue;
			int d = id[q];
			//printf("AC find %d\n", d);
			++over[d];
			if (last_pos[d] + len[d] <= l) {
				++n_over[d];
				last_pos[d] = l;
			}
		}
	}
}

int Find(const char *s) {
	int p = 0;
	for (; *s; ++s) {
		p = nd[p][ch_num[*s]];
	}
	return id[p];
}

int main()
{
	for (int i = 0; i < MAX_CHILD; ++i) ch_num['a'+i] = i;
	int nCase = 0;
	while (EOF != scanf("%s", str)) {
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		id[0] = 0;
		nd_cnt = 1;
		int n;
		scanf("%d", &n);
		ID = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d%s", &qry[i].d, qry[i].word);
			int id = insert(qry[i].word);
			len[id] = strlen(qry[i].word);
			over[id] = 0;
			n_over[id] = 0;
			last_pos[id] = -1;
		}
		AC_construct();
		AC_find(str);

		printf("Case %d\n", ++nCase);
		for (int i = 0; i < n; ++i) {
			int id = Find(qry[i].word);
			if (qry[i].d == 0) {
				printf("%d\n", over[id]);
			} else {
				printf("%d\n", n_over[id]);
			}
		}
		printf("\n");
	}
	return 0;
}
