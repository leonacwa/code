/* AC自动机 + 状态DP
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
const int MAX_CHILD = 26;
char ch_num[128];

int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int ss[MAXN];
int ww[MAXN];

char word[105][16];
int weight[105];

int f[51][MAXN];
char fw[51][MAXN][51];

void insert(const char *s, int v, int w) {
	int p = 0;
	for (; *s; ++s) {
		int i = ch_num[*s];
		if (nd[p][i] == 0) {
			memset(nd[nd_cnt], 0, sizeof(nd[nd_cnt]));
			fail[nd_cnt] = 0;
			ss[nd_cnt] = 0;
			ww[nd_cnt] = 0;
			nd[p][i] = nd_cnt++;
		}
		p = nd[p][i];
	}
	ss[p] = v;
	ww[p] = w;
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
				ww[v] += ww[fail[v]];
			} else {
				nd[q][i] = nd[fail[q]][i];
			}
		}
	}
}

int main()
{
	for (int i = 0; i < MAX_CHILD; ++i) ch_num['a'+i] = i;
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		ss[0] = 0;
		ww[0] = 0;
		nd_cnt = 1;
		weight[0] = 0;
		word[0][0] = 0;
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i) scanf("%s", word[i]);
		for (int i = 1; i <= m; ++i) scanf("%d", &weight[i]);
		for (int i = 1; i <= m; ++i) {
			insert(word[i], i, weight[i]);
		}
		AC_construct();
		//puts("ac end");
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j < nd_cnt; ++j) {
				f[i][j] = -1;
				fw[i][j][0] = 0;
			}
		}
		f[0][0] = 0;
		fw[0][0][0] = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < nd_cnt; ++j) {
				if (f[i][j] == -1) continue;
				for (int s = 0; s < MAX_CHILD; ++s) {
					int c = nd[j][s];
					if (f[i+1][c] < f[i][j] + ww[c]) {
						f[i+1][c] = f[i][j] + ww[c];
						strcpy(fw[i+1][c], fw[i][j]);
						fw[i+1][c][i] = 'a' + s;
						fw[i+1][c][i+1] = 0;
					} else if (f[i+1][c] == f[i][j] + ww[c]) {
						char str[52];
						strcpy(str, fw[i][j]);
						str[i] = 'a' + s;
						str[i+1] = 0;
						if (fw[i+1][j][0] == 0 || strcmp(str, fw[i+1][c]) < 0) {
							strcpy(fw[i+1][c], str);
						}
					}
				}
			}
		}
		char ans[52] = {0};
		int wa = 0, len = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < nd_cnt; ++j) {
				//printf(":%s %d\n", fw[i][j], f[i][j]);
				if (wa < f[i][j]) {
					wa = f[i][j];
					strcpy(ans, fw[i][j]);
					len = i;
				} else if (wa == f[i][j] && i == len && strcmp(ans, fw[i][j]) > 0) {
					strcpy(ans, fw[i][j]);
				}
			}
		}
	//	printf("%d  ", wa);
		puts(ans);
	}
	return 0;
}

