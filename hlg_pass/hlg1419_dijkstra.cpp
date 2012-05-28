#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long llong;
const int MAXN = 50000 + 10;

struct Edge {
	int to, len;
	Edge *next;
};
int nE;
Edge *head[MAXN];
Edge E[MAXN * 2];

void addEdge(int u, int v, int len)
{
	Edge *e = E + nE++;
	e->to = v;
	e->len = len;
	e->next = head[u];
	head[u] = e;
}

bool vis[MAXN];
struct Node {
	int v;
	llong len;
	bool operator < (const Node &B) const {
		return len > B.len;
	}
} vHeap[MAXN];

void dijkstra(int n, int s, Edge *head[], llong len[])
{
	memset(vis, 0, sizeof(vis[0]) * (n + 1));
	memset(len, -1, sizeof(len[0]) * (n + 1));
	len[s] = 0;
	int cnt = 1;
	vHeap[0].v = s;
	vHeap[0].len = 0;
	for (int i = 0; i < n; ++i) {
		int u = -1;
		llong minLen = -1;
		while (cnt > 0) {
			u = vHeap[0].v;
			minLen = vHeap[0].len;
			pop_heap(vHeap, vHeap + cnt);
			--cnt;
			if (!vis[u]) {
				break;
			}
			u = -1;
		}
		if (u == -1) break;
		vis[u] = true;
		for (Edge *e = head[u]; e; e = e->next) {
			if (!vis[e->to] && (len[e->to] == -1 || len[e->to] > minLen + e->len)) {
				len[e->to] = minLen + e->len;
				vHeap[cnt].v = e->to;
				vHeap[cnt].len = len[e->to];
				++cnt;
				push_heap(vHeap, vHeap + cnt);
			}
		}
	}
}

int weight[MAXN];
llong len[MAXN];

int main()
{
	int nTest;
	int n, e;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d", &n, &e);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &weight[i]);
		}
		nE = 0;
		memset(head, 0, sizeof(head));
		for (int i = 0; i < e; ++i) {
			int a, b, w;
			scanf("%d %d %d", &a, &b, &w);
			addEdge(a, b, w);
			addEdge(b, a, w);
		}

		dijkstra(n, 1, head, len);
		llong ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (len[i] < 0) {
				ans = -1;
				break;
			}
			ans += weight[i] * len[i];
		}
		if (ans >= 0) {
			printf("%lld\n", ans);
		} else {
			puts("No Answer");
		}
	}
	return 0;
}

