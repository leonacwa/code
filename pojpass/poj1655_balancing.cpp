#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

const int NN = 20001;
struct Edge {
	int v;
	struct Edge *next;
};
int id, ans, n;
int nE;
Edge E[NN*2];
Edge* head[NN];
int cnt[NN];

void addEdge(int u, int v)
{
	E[nE].v = v;
	E[nE].next = head[u];
	head[u] = E + nE;
	++nE;
}

void dfs(int p, int pr)
{
	cnt[p] = 1;
	for (Edge *e = head[p]; e; e = e->next) {
		int c = e->v;
		if (c == pr) continue;
		dfs(c, p);
		cnt[p] += cnt[c];
	}
	int t = n - cnt[p];
	for (Edge *e = head[p]; e; e = e->next) {
		int c = e->v;
		if (c == pr) continue;
		if (t < cnt[c]) {
			t = cnt[c];
		}
	}
	if (ans > t || (ans == t && id > p)) {
		ans = t;
		id = p;
	}
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		memset(cnt, 0, sizeof(cnt));
		memset(head, 0, sizeof(head));
		nE = 0;
		scanf("%d", &n);
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
		}
		id = INT_MAX, ans = INT_MAX;
		dfs(1, -1);
		printf("%d %d\n", id, ans);
	}
	return 0;
}

