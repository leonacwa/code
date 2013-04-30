/* AC自动机模板，数组版
 * 基于hdu2222 Keyword Search
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 50 * 10000 + 100;
const int MAX_CHILD = 26;
char ch_num[128];

int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int ss[MAXN];

void insert(const char *s) {
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
				int t = fail[q];
				while (nd[t][i] == 0 && t != 0) t = fail[t];
				fail[v] = nd[t][i];
				ss[v] += ss[fail[v]];
			} else {
				nd[q][i] = nd[fail[q]][i];
			}
		}
	}
}

int AC_find(const char *s)
{
	int ret = 0, p = 0, q, i;
	for (; *s; ++s) {
		i = ch_num[*s];
		while (p != 0 && nd[p][i] == 0) p = fail[p];
		q = p = nd[p][i];
		while (q != 0 && ss[q] != -1) {
			ret += ss[q];
			ss[q] = -1;
			q = fail[q];
		}
	}
	return ret;
}

char str[1000000+100];
int main()
{
    for (int i = 0; i < MAX_CHILD; ++i) ch_num[i+'a'] = i;
    int nTest;
    scanf("%d", &nTest);
    while (nTest--) {
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		ss[0] = 0;
        nd_cnt = 1;
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            insert(str);
        }
        AC_construct();
        scanf("%s", str);
        printf("%d\n", AC_find(str));
    }
    return 0;
}

