/* 强连通分量 tarjan算法
 * 时间复杂度O(V+E)
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 1005;
const int MAXM = 12005;

struct Arc {
	int to;
	Arc * next;
	Arc() {}
	Arc(int tto, Arc *tn) : to(tto), next(tn) {}
};
int nA;
Arc A[MAXM], *V[MAXN];
int order, vis[MAXN], low[MAXN];
int sc_cnt, top, vstack[MAXN], id[MAXN]; // sc_cnt 强连通分量个数，id[]每个顶点所属的强连通分量编号
bool instack[MAXN];

void addArc(int u, int v) {
	A[nA] = Arc(v, V[u]);
	V[u] = A + nA++;
}

void init_sc_tarjan() {
	memset(vis, 0, sizeof(vis));
	memset(instack, 0, sizeof(instack));
	top = -1;
	order = 0;
	sc_cnt = 0;
}

void sc_tarjan(int u) {
	vis[u] = low[u] = ++order;
	instack[u] = true;
	vstack[++top] = u;
	int v;
	for (Arc *a = V[u]; a; a = a->next) {
		v = a->to;
		if (vis[v] == 0) {
			sc_tarjan(v);
			if (low[u] > low[v]) low[u] = low[v];
		} else if (instack[v] && low[u] > vis[v]) {
			low[u] = vis[v];
		}
	}
	if (vis[u] == low[u]) {
		do {
			v = vstack[top--];
			instack[v] = false;
			id[v] = sc_cnt; // 顶点v所在连通分量的集合
		} while (u != v);
		sc_cnt++;
	}
}

int main()
{
	// read data
	init_sc_tarjan();
	for (int i = 1; i <= n; ++i) {
		if (vis[i] == 0) {
			sc_tarjan(i);
		}
	}
	printf("strong connect %d\n", sc_cnt);
	return 0;
}
