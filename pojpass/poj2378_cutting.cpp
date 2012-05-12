#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
#include <iostream>
using namespace std;

const int NN = 10001;
struct Edge {
	int v;
	struct Edge *next;
};
int n, n_half;
int nE;
Edge E[NN*2];
Edge* head[NN];
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
	cnt[p] = 1;
	for (Edge *e = head[p]; e; e = e->next) {
		int c = e->v;
		if (c == pr) continue;
		dfs(c, p);
		cnt[p] += cnt[c];
	}
	int t = n - cnt[p];
	if (t > n_half) return;
	for (Edge *e = head[p]; e; e = e->next) {
		int c = e->v;
		if (c == pr) continue;
		if (cnt[c] > n_half) return;
	}
	ans[c_ans++] = p;
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		memset(cnt, 0, sizeof(cnt));
		memset(head, 0, sizeof(head));
		nE = 0;
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
		}
		c_ans = 0;
		n_half = n / 2;
		dfs(1, -1);
		sort(ans, ans + c_ans);
		if (c_ans == 0) {
			puts("NONE");
		} else {
			for (int i = 0; i < c_ans; ++i) {
				printf("%d\n", ans[i]);
			}
		}
	}
	return 0;
}

