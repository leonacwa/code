#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 50001;
struct Edge {
	int v;
	struct Edge *next;
};

int nE, n, k, ans;
Edge E[NN*2];
Edge *head[NN];
int cnt[NN][501];

void addEdge(int u, int v) 
{
	Edge *p = E + nE++;
	p->v = v;
	p->next = head[u];
	head[u] = p;
}

void dfs(int p, int pr)
{
	memset(cnt[p], 0, sizeof(cnt[p]));
	cnt[p][0] = 1;
	for (Edge *e = head[p]; e; e = e->next) {
		int v = e->v;
		if (v == pr) continue;
		dfs(v, p);
		for (int i = 0; i < k; ++i) {
			ans += cnt[p][i] * cnt[v][k - i - 1];
		}
		for (int i = 1; i <= k; ++i) {
			cnt[p][i] += cnt[v][i-1];
		}
	}
	//ans += cnt[p][k];
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		nE = 0;
		memset(head, 0, sizeof(head));
		scanf("%d %d", &n, &k);
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
		}
		ans = 0;
		dfs(1, -1);
		printf("%d\n", ans);
	}
	return 0;
}

