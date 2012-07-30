/* AC自动机+DP+节点数剪枝
 * 裸的状态方程：f[s+js] = min(f[s][j] + 1) js是j是子节点，s+js表示到达js节点时包含的资源串
 * 这个方程时间复杂度太高，要压缩。
 * 因为只有尾节点为资源时才是有效的，所以只考虑资源串,可以BFS计算出两个资源串的距离，然后DP
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 60000 + 100;
const int MAX_CHILD = 2;
char ch_num[128];

int nd_cnt;
int nd[MAXN][MAX_CHILD];
int fail[MAXN];
int ss[MAXN];

char str[MAXN];

int addr[11];
int g[11][11];
int dis[MAXN];
int mark[MAXN];

int f[1<<10][11];

void insert(const char *s, int v) {
	int p = 0;
	for (; *s; ++s) {
		int i = ch_num[*s];
		if (nd[p][i] == 0) {
			memset(nd[nd_cnt], 0, sizeof(nd[nd_cnt]));
			fail[nd_cnt] = 0;
			ss[nd_cnt] = -1;
			nd[p][i] = nd_cnt++;
		}
		p = nd[p][i];
	}
	ss[p] = v;
	addr[v] = p;
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
			} else {
				nd[q][i] = nd[fail[q]][i];
			}
		}
	}
}

int bfs_dis(int st)
{
	for (int i = 0; i < nd_cnt; ++i) dis[i] = -1;
	dis[st] = 0;
	int *s = Q, *e = Q;
	*e++ = st;
	mark[st] = st;
	while (s != e) {
		int q = *s++;
		mark[q] = st;
		for (int i = 0; i < MAX_CHILD; ++i) {
			int son = nd[q][i];
			if (ss[son] == -2) continue;
			if (mark[son] != st && (dis[son] == -1)) {// || dis[son] > dis[q] + 1)) {
				dis[son] = dis[q] + 1;
				*e++ = son;
			}
		}
	}
}

inline bool test_bit(int s, int i) {
	return s & (1<<i);
}

int main()
{
	ch_num['0'] = 0;
	ch_num['1'] = 1;
	int n, m;
    while (EOF != scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		memset(nd[0], 0, sizeof(nd[0]));
		fail[0] = 0;
		ss[0] = -1;
        nd_cnt = 1;
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            insert(str, i);
        }
		for (int i = 0; i < m; ++i) {
            scanf("%s", str);
			insert(str, -2);
		}
        AC_construct();
		
		// shortees path between resorce node
		memset(f, -1, sizeof(f));
		f[0][0] = 0;
		for (int i = 0; i < nd_cnt; ++i) mark[i] = -1;
		bfs_dis(0);
		for (int i = 0; i < n; ++i) {
			f[1<<i][i] = dis[addr[i]];
		}
		for (int i = 0; i < n; ++i) {
			bfs_dis(addr[i]);
			for (int j = 0; j < n; ++j) {
				if (mark[addr[j]] == addr[i]) {
					g[i][j] = dis[addr[j]];
				} else {
					g[i][j] = -1;
				}
			}
		}
		int sum = 1 << n;
		for (int s = 1; s < sum; ++s) {
			for (int i = 0; i < n; ++i) {
				if (!test_bit(s, i) || f[s][i] == -1) continue;
				for (int j = 0; j < n; ++j) {
					if (test_bit(s, j) || g[i][j] == -1) continue;
					int s2 = s | (1<<j);
					int t = f[s][i] + g[i][j];
					if (f[s2][j] == -1 || f[s2][j] > t) {
						f[s2][j] = t;
					}
				}
			}
		}

		int ans = -1;
		for (int i = 0; i < n; ++i) {
			if (f[sum-1][i] != -1 && (ans == -1 || ans > f[sum-1][i])) ans = f[sum-1][i];
		}
		printf("%d\n", ans);
    }
    return 0;
}

