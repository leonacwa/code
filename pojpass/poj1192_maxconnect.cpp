//  树形DP
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 1001;

struct Edge{
	int v;
	Edge * next;
};
int nE;
Edge *head[NN];
Edge E[NN * NN];

void addEdge(int u, int v)
{
	Edge * e = E + nE++;
	e->v = v;
	e->next = head[u];
	head[u] = e;
}
int ans;
int X[NN], Y[NN], W[NN];
bool vis[NN];

int dfs(int u, int pr)
{
	int ret = W[u];
	vis[u] = true;
	for (Edge *e = head[u]; e; e = e->next) {
		if (vis[e->v]) continue;
		int t = dfs(e->v, u);
		if (t > 0) {
			ret += t;
		}
	}
	if (ret > ans) {
		ans = ret;
	}
	return ret;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d %d %d", &X[i], &Y[i], &W[i]);
	}
	nE = 0;
	memset(head, 0, sizeof(head));
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (abs(X[i] - X[j]) + abs(Y[i] - Y[j]) == 1) {
				addEdge(i, j);
				addEdge(j, i);
			}
		}
	}
	memset(vis, 0, sizeof(vis));
	ans = 0;
	int t = dfs(0, -1);
	ans = max(t, ans);
	printf("%d\n", ans);
	return 0;
}

