#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <map>
using namespace std;

const int NN = 100000 + 10;
struct Edge {
	int v;
	Edge *next;
};

int nE, n;
Edge E[NN];
Edge *head[NN];
int ID;
int d[NN], f[NN];

void addEdge(int u, int v)
{
	Edge *e = E + nE++;
	e->v = v;
	e->next = head[u];
	head[u] = e;
}

void dfs(int p, int pr)
{
	d[p] = ++ID;
	for (Edge *e = head[p]; e; e = e->next) {
		if (e->v == pr) continue;
		dfs(e->v, p);
	}
	f[p] = ++ID;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		nE = 0;
		memset(head, 0, sizeof(head));
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			int p;
			scanf("%d", &p);
			addEdge(p, i + 1);
		}
		ID = 0;
		dfs(0, -1);
		int q;
		scanf("%d", &q);
		for (int i = 0; i < q; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			if (d[u] < d[v] && f[v] < f[u]) {
				printf("%d>%d\n", u, v);
			} else if (d[v] < d[u] && f[u] < f[v]) {
				printf("%d<%d\n", u, v);
			} else {
				printf("%d<>%d\n", u, v);
			}
		}
	}
	return 0;
}

