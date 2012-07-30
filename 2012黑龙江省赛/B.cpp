/* AC自动机模板，数组版
 * 基于hdu2222 Keyword Search
 * 2012黑龙江省赛B
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 404200 + 100;
const int MAX_CHILD = 26;
char ch_num[128];

int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int ss[MAXN];

char pwd[32], word[32];
char str[1000000+100];
bool vis[32];

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
	//ss[p] |= 1<<(v-1);
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
				int t = fail[q];
				while (nd[t][i] == 0 && t != 0) t = fail[t];
				fail[v] = nd[t][i];
				//ss[v] |= ss[fail[v]];
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
		//while (p != 0 && nd[p][i] == 0) p = fail[p];
		q = p = nd[p][i];
		while (q != 0 && ss[q] != -1) {
			if (ss[q] > 0) {
				if (!vis[ss[q]]) ++ret;
				vis[ss[q]] = true;
				ss[q] = -1;
			}
			break;
			ret |= ss[q];
			ss[q] = -1;
			q = fail[q];
		}
	}
	return ret;
	int ans = 0;
	while (ret) {
		if (ret & 1) ++ans;
		ret >>= 1;
	}
	return ans;
}

int main()
{
    for (int i = 0; i < MAX_CHILD; ++i) ch_num[i+'a'] = i;
    while (EOF != scanf("%s", str)) {
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		ss[0] = 0;
        nd_cnt = 1;
        int m, n, a = -1, b = -1;
        scanf("%d%s", &m, pwd);
		for (int i = 0; i < m; ++i) {
			if (pwd[i] == '1') {
				if (a == -1) a = i;
				else if (b == -1) b = i;
				else puts("error");
			}
		}
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			vis[i] = false;
			scanf("%s", word);
			if (a == -1 && b == -1) {
				insert(word, i);
			} else if (a != -1 && b == -1) {
				for (char ac = 'a'; ac <= 'z'; ++ac) {
					word[a] = ac;
					insert(word, i);
				}
			} else {
				for (char ac = 'a'; ac <= 'z'; ++ac) {
					word[a] = ac;
					for (char bc = 'a'; bc <= 'z'; ++bc) {
						word[b] = bc;
						insert(word, i);
					}
				}
			}
		}
        AC_construct();
        printf("%d\n", AC_find(str));
    }
    return 0;
}

