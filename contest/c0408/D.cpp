#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>
using namespace std;
const int NN = 5000+1;
const int MM = 10000+1;

struct Edge {
	int w, v;
	Edge *next;
};
int nE, n, m, A, B, C;
Edge *head[NN];
Edge E[MM*2];

void addEdge(int u, int v, int w)
{
	E[nE].v = v;
	E[nE].w = w;
	E[nE].next = head[u];
	head[u] = E + nE;
	++nE;
}

struct Cost {
	int u;
	long long w;
	bool operator < (const Cost &B) {
		return w > B.w;
	}
};

bool vis[NN];
long long costA[NN], costB[NN], costC[NN];
Cost minCost[MM];

void dijkstra(int s, long long cost[NN])
{
	for (int i = 0; i <= n; ++i) {
		cost[i] = INT_MAX;
		vis[i] = false;
	}
	cost[s] = 0;
	int cnt = 1;
	minCost[0].u = s;
	minCost[0].w = 0;
	for (int i = 1; i <= n; ++i) {
		if (cnt <= 0) break;
		int minW = minCost[0].w;
		int u = minCost[0].u;
		pop_heap(minCost, minCost + cnt);
		--cnt;
		if (vis[u]) continue;
		vis[u] = true;
		for (Edge *e = head[u]; e; e = e->next) {
			int v = e->v;
			if (vis[v]) continue;
			if (cost[v] > minW + e->w) {
				cost[v] = minW + e->w;
				minCost[cnt].u = v;
				minCost[cnt].w = cost[v];
				++cnt;
				push_heap(minCost, minCost + cnt);
			}
		}
		while (cnt > 0 && vis[minCost[0].u]) {
			pop_heap(minCost, minCost + cnt);
			--cnt;
		}
		if (cnt <= 0) break;
	}
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d", &n, &m)) {
		memset(head, 0, sizeof(head));
		nE = 0;
		scanf("%d %d %d", &C, &A, &B);
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			addEdge(u, v, w);
			addEdge(v, u, w);
		}
		dijkstra(C, costC);
		dijkstra(A, costA);
		dijkstra(B, costB);
		long long ans = INT_MAX;
		for (int i = 1; i <= n; ++i) {
			long long t = costC[i] + costA[i] + costB[i];
			if (ans > t) ans = t;
		}
		printf("Scenario #%d\n", ++nCase);
		if (ans >= INT_MAX) {
			printf("Can not reah!\n\n");
		} else {
			printf("%lld\n\n", ans);
		}
	}
	return 0;
}

