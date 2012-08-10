#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <cfloat>
#include <algorithm>
using namespace std;

const int MAXN = 500100; // 节点个数
const double DBL_INF = 1e30;
struct Edge {
	int to;
	double len;
	Edge *next;
};
int nE;
Edge *head[MAXN];
Edge E[2500000];
double len[MAXN];

void addEdge(int u, int v, double len) {
	Edge *e = E + nE++;
	e->to = v;
	e->len = len;
	e->next = head[u];
	head[u] = e;
}

bool vis[MAXN];
struct Node {
	int v;
	double len;
	bool operator < (const Node &B) const {
		return len > B.len;
	}
} vHeap[MAXN*4]; // 堆的大小要尽量大些

// 顶点个数n，源点s，顶点的边集链表头head[]，返回的距离数组 len[]
void dijkstra(int n, int s, int dst)
{
	memset(vis, 0, sizeof(vis[0]) * (n + 1));
	for (int i = 0; i <= n; ++i) len[i] = DBL_INF;
	int cnt = 1;
	vHeap[0].v = s;
	vHeap[0].len = 0;
	len[s] = 0;
	for (int i = 0; i < n; ++i) {
		int u = -1;
		while (cnt > 0) {
			u = vHeap[0].v;
			pop_heap(vHeap, vHeap + cnt);
			--cnt;
			if (!vis[u]) break;
			u = -1;
		}
		if (u == -1) break;
		vis[u] = true;
		if (dst == u) break;
		for (Edge *e = head[u]; e; e = e->next) {
			if (vis[e->to]) continue;
			int v = e->to;
			double t = len[u] + e->len - len[u] * e->len;
			if (len[v] > t) {
				len[v] = t;
				vHeap[cnt].v = v;
				vHeap[cnt].len = len[v];
				++cnt;
				push_heap(vHeap, vHeap + cnt);
			}
		}
	}
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		nE = 0;
		memset(head, 0, sizeof(head));
		for (int i = 1, k; i <= n; ++i) {
			scanf("%d", &k);
			for (int j = 0, a, b; j < k; ++j) {
				scanf("%d%d", &a, &b);
				addEdge(i, a, b / 100.0);
			}
		}
		int s, t, m;
		scanf("%d%d%d", &s, &t, &m);
		dijkstra(n, s, t);
		double f = m * len[t];
	//	printf("dst %f\n", f);
		if (f >= m) puts("IMPOSSIBLE!");
		else printf("%.2f\n", f);
	}
	return 0;
}

