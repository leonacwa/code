/* The war [The 36th ACM/ICPC Asia Regional Dalian Site —— Online Contes];
 * http://acm.hdu.edu.cn/showproblem.php?pid=4005
 * 无向图双连通分量+缩点+dfs寻找分叉中第二小的边
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


const int INF = 99999999;
const int MAXN = 10005, MAXM = 200005;

struct Arc {
	int from, to;
	int w;
	Arc *next;
};
Arc A[MAXM], *V[MAXN], E[MAXM];
int nA, nE;

int stk[MAXM];
int top, sc_cnt, order;
int low[MAXN], vis[MAXN];
int fa[MAXN];
bool instk[MAXN];

void addArc(int u, int v, int w) {
	Arc *a = A + nA++;
	a->from = u, a->to = v, a->w = w, a->next = V[u];
	V[u] = a;
}

void sc_tarjan(int u, int pu) {
	vis[u] = low[u] = ++order;
	stk[++top] = u;
	instk[u] = true;
	int v;
	for (Arc *a = V[u]; a; a = a->next) {
		if (a->to == pu) continue;
		v = a->to;
		if (vis[v] == -1) {
			sc_tarjan(v, u);
			if (low[u] > low[v]) low[u] = low[v];
			if (vis[u] < low[v]) { // 割边
				E[nE++] = *a;
			}
		} else if (instk[v] && low[u] > vis[v]) low[u] = vis[v];
	}
	if (vis[u] == low[u]) {
		do {
			v = stk[top--];
			fa[v] = sc_cnt;
			instk[v] = false;
		} while (top > 0 && u != v);
		sc_cnt++;
	}
}

int ans;
int dfs(int u, int pu) { // 在分叉中找第二小
	vis[u] = 1;
	int minlen = INF, r;
	for (Arc *a = V[u]; a; a = a->next) {
		if (a->to == pu || vis[a->to] != -1) continue;
		r = dfs(a->to, u);
		if (r > a->w) r = a->w;
		if (minlen > r) {
			if (ans > minlen) ans = minlen;
			minlen = r;
		} else {
			if (ans > r) ans = r;
		}
	}
	return minlen;
}

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		memset(V, 0, sizeof(V));
		nA = 0;
		for (int i = 0, a, b, c; i < m; ++i) {
			scanf("%d%d%d", &a, &b, &c);
			addArc(a, b, c);
			addArc(b, a, c);
		}
		memset(instk, 0, sizeof(instk));
		memset(vis, -1, sizeof(vis));
		memset(low, -1, sizeof(low));
		sc_cnt = order = top = 0;
		nE = 0;
		sc_tarjan(1, -1);

		memset(V, 0, sizeof(V));
		nA = 0;
		int k = -1;
		for (int i = 0; i < nE; ++i) {
			int u = fa[E[i].from], v = fa[E[i].to], w = E[i].w;
			if (u != v) {
				addArc(u, v, w);
				addArc(v, u, w);
				if (k == -1 || E[k].w > E[i].w) k = i;
			}
		}
		if (k == -1) {
			puts("-1");
			continue;
		}
		memset(vis, -1, sizeof(vis));
		int u = fa[E[k].from], v = fa[E[k].to];
		vis[u] = vis[v] = 1;
		ans = INF;
		dfs(u, -1);
		dfs(v, -1);
		if (ans == INF) puts("-1");
		else printf("%d\n", ans);
	}
	return 0;
}
