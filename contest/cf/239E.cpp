/*
 * CF 239 E. World Eater Brothers
 * 枚举 + 树形DP
 * 点的个数n<=3000，n*n<=9000000，不到一千万，1s能跑完。
 * 枚举第一个点，从i开始遍历，得到所需的反向的边数total，然后枚举第二个点，假如是j，可以想象成有两个源点i j，要走完i和j之间的点，最少要变多少边方向，因为从i到j的已经包含在total里了，现在要判断从j到i的方向，要走多少，改变多少反向边。可以统计有多少边可以从j走向i，期间可以让j到i之间的反向边反向，此时的统计就要减去改变方向的边数了。
 * 剩下的想想就有解了。
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 3005, MAXM = MAXN * 2;

struct Edge {
	int to;
	int w;
	Edge *next;
};
int n, nE;
Edge E[MAXM], *V[MAXN];

void addEdge(int u, int v, bool w) {
	Edge *e = E + nE++;
	e->to = v;
	e->w = w;
	e->next = V[u];
	V[u] = e;
}

int total, tmax;

void  dfs(int u,int pu, int tval) {
	if (tval < 0) tval = 0;
	tmax = max(tmax, tval);
	for (Edge *e = V[u]; e; e = e->next) {
		if (pu != e->to) {
			if (e->w) {
				++total;
				dfs(e->to, u, tval + 1);
			} else {
				dfs(e->to, u, tval - 1);
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0, a, b; i < n-1; ++i) {
		scanf("%d%d", &a, &b);
		--a, --b;
		addEdge(a, b, 0);
		addEdge(b, a, 1);
	}
	int ans = 9999999;
	for (int i = 0; i < n; ++i) {
		total = tmax = 0;
		dfs(i, -1, 0);
		ans = min(ans, total - tmax);
	}
	printf("%d\n", ans);
	return 0;

}
