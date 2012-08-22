#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LLONG;
const int NN = 1000000 + 5;

struct Edge {
	int v, w;
	Edge * next;
};
int nE, nAE;
Edge *head[NN], * Ahead[NN];
Edge E[NN], AE[NN];

void addEdge(int u, int v, int w)
{
	Edge *e = E + nE++;
	e->v = v;
	e->w = w;
	e->next = head[u];
	head[u] = e;

	e = AE + nAE++;
	e->v = u;
	e->w = w;
	e->next = Ahead[v];
	Ahead[v] = e;
}

bool vis[NN];
struct PVex {
	int v;
	LLONG w;
	bool operator < (const PVex &B) const {
		return w > B.w;
	}
} pri_ord[NN];

void dijkstra(int n, int s, Edge *head[], LLONG len[])
{
	memset(len, -1, sizeof(len[0]) * (n + 1));
	memset(vis, 0, sizeof(vis[0]) * (n + 1));
	len[s] = 0;
	int cnt = 1;
	pri_ord[0].v = s;
	pri_ord[0].w = 0;
	for (int i = 0; i < n; ++i) {
		if (cnt <= 0) {
			break;
		}
		int u = pri_ord[0].v;
		pop_heap(pri_ord, pri_ord + cnt);
		--cnt;
		vis[u] = true;
		for (Edge *e = head[u]; e; e = e->next) {
			int v = e->v;
			LLONG w = e->w;
			if (!vis[v] && (len[v] == -1 || len[v] > len[u] + w)) {
				len[v] = len[u] + w;
				pri_ord[cnt].v = v;
				pri_ord[cnt].w = len[v];
				++cnt;
				push_heap(pri_ord, pri_ord + cnt);
			}
		}
		while (cnt > 0 && vis[pri_ord[0].v]) {
			pop_heap(pri_ord, pri_ord + cnt);
			--cnt;
		}
	}
}

LLONG len[NN], Alen[NN];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, q;
		scanf("%d %d", &n, &q);
		nE = nAE = 0;
		memset(head, 0, sizeof(head[0]) * (n + 1));
		memset(Ahead, 0, sizeof(Ahead[0]) * (n + 1));
		for (int i = 0; i < q; ++i) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			addEdge(u, v, w);
		}
		dijkstra(n, 1, head, len);
		dijkstra(n, 1, Ahead, Alen);
		LLONG ans = 0;
		for (int i = 1; i <= n; ++i) {
			ans += len[i] + Alen[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}

