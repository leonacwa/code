/* LCA问题 tarjan 解法
 * 离线算法，时间复杂度 O(n)
 * poj 1986
**/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 40000 + 5;
struct Edge {
	int to, len;
	Edge * next;
};
int nE;
Edge E[MAXN * 2];
Edge *head[MAXN];

void addEdge(int u, int v, int len) {
	Edge *e = E + nE++;
	e->to = v;
	e->len = len;
	e->next = head[u];
	head[u] = e;
}

struct QueryEdge {
	int to, id;
	QueryEdge * next;
};
int nQE;
int ans[MAXN];
QueryEdge QE[MAXN * 2];
QueryEdge * Qhead[MAXN];

void addQueryEdge(int u, int v, int id) {
	QueryEdge *e = QE + nQE++;
	e->to = v;
	e->id = id;
	e->next = Qhead[u];
	Qhead[u] = e;
}
int pa[MAXN]; // 用于并查集
int find(int x) {
	if (x != pa[x]) {
		pa[x] = find(pa[x]);
	}
	return pa[x];
}

void join(int a, int b) {
	int fa = find(a), fb = find(b);
	if (fa != fb) {
		pa[b] = fa;
	}
}

int dep[MAXN];  // 深度
int anc[MAXN]; // 祖先
// 起点u, u的前驱pr, u的深度(距离)depth
void tarjan_lca(int u, int pr, int depth) {
	dep[u] = depth;
	anc[find(u)] = u;
	for (Edge *e = head[u]; e; e = e->next) {
		if (dep[e->to] != -1) continue;
		tarjan_lca(e->to, u, depth + e->len);
		join(u, e->to); 
		anc[find(u)] = u;
	}
	for (QueryEdge * e = Qhead[u]; e; e = e->next) { // u 和e->to 的最近公共祖先是anc[find(e->to)]
		if (dep[e->to] != -1) {
			ans[e->id] = dep[e->to] + dep[u] - 2 * dep[anc[find(e->to)]];
		}
	}
}

int main() {
	int n, m;
	while (EOF != scanf("%d %d", &n, &m)) {
		for (int i = 0; i <= n; ++i) {
			pa[i] = i;
			dep[i] = -1;
		}
		nE = nQE = 0;
		memset(head, 0, sizeof(head));
		memset(Qhead, 0, sizeof(Qhead));
		for (int i = 0; i < m; ++i) {
			int a, b, l;
			scanf("%d %d %d %*s", &a, &b, &l);
			addEdge(a, b, l);
			addEdge(b, a, l);
		}
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; ++i) {
			int a, b;
			scanf("%d %d", &a, &b);
			addQueryEdge(a, b, i);
			addQueryEdge(b, a, i);
		}
		tarjan_lca(1, 0, 0); // 1是树的根
		for (int i = 0; i < k; ++i) { // 回答问题
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}