/* Ticket to Ride 
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

const int MAXN = 105;
const int MAXM = 1005;

struct Edge {
	int u, v, w;
} E[MAXM], res[4];
bool used[MAXM];

bool cmpw(const Edge &A, const Edge &B) {
	return A.w < B.w;
}

int fa[MAXN];
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		fa[fy] = fx;
	}
}

int check(int n, int m) {
	int ret = 0;
	for (int i = 0; i <= n; ++i) fa[i] = i;
	for (int i = 0; i <= m; ++i) {
		if (used[i] && find(E[i].u) != find(E[i].v)) {
			ret += E[i].w;
			join(E[i].u, E[i].v);
		}
	}
	for (int i = 0; i < 4; ++i) {
		if (find(res[i].u) != find(res[i].v)) {
			return -1;
		}
	}
	return ret;
}

int ans;
void dfs(int n, int r, int start) {
	if (start == -1) return;
	for (int i = start; i >= 0; --i) {
		used[i] = false;
		int ret = check(n, r); 
		if (ret != -1) {
			if (ans >= ret) {
				ans = ret;
			}
				dfs(n, r, i-1);
		}
		used[i] = true;
	}
}

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		map<string, int> ma;
		char str[256], str2[256];
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str);
			ma[str] = i;
		}
		for (int i = 0, w; i < m; ++i) {
			scanf("%s%s%d", str, str2, &w);
			E[i].u = ma[str], E[i].v = ma[str2], E[i].w = w;
		}
		for (int i = 0; i < 4; ++i) {
			scanf("%s%s", str, str2);
			res[i].u = ma[str], res[i].v = ma[str2];
		}
		memset(used, 1, sizeof(used));
		sort(E, E + m, cmpw);
		int l = 0, r = m - 1, ret;
		while (l < r) {
			int mid = (l + r) >> 1;
			ret = check(n, mid);
			if (ret != -1) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}
		ans = check(n, r);
		dfs(n, r, r);
		/*
		   for (int i = 0; i <= r; ++i) {
		   if (used[i]) printf("%d:%d -> %d  %d\n", i, E[i].u, E[i].v, E[i].w);
		   }
		   */
		printf("%d\n", ans);
	}
	return 0;
}
