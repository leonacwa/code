#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

const int NN = 50001;
struct Edge {
	int v;
	struct Edge* next;
};
int nE, n;
Edge *head[NN];
Edge E[NN*2];
int max_child;
int cnt[NN];
int c_ans, ans[NN];

void addEdge(int u, int v)
{
	E[nE].v = v;
	E[nE].next = head[u];
	head[u] = E + nE;
	++nE;
}

void dfs(int p, int pr)
{
	int t = 0;
	cnt[p] = 1;
	for (Edge *e = head[p]; e; e = e->next) {
		int c = e->v;
		if (c == pr) continue;
		dfs(c, p);
		cnt[p] += cnt[c];
		if (t < cnt[c]) {
			t = cnt[c];
		}
	}
	if (t < n - cnt[p]) {
		t = n - cnt[p];
	}
	if (t < max_child) {
		max_child = t;
		ans[0] = p;
		c_ans = 1;
	} else if (t == max_child) {
		ans[c_ans++] = p;
	}
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		memset(head, 0, sizeof(head));
		nE = 0;
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
		}
		c_ans = 0;
		max_child = INT_MAX;
		dfs(1, -1);
		sort(ans, ans + c_ans);
		for (int i = 0; i < c_ans-1; ++i) {
			printf("%d ", ans[i]);
		}
		printf("%d\n", ans[c_ans-1]);
	}
	return 0;
}

