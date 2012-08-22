#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 5005;
const int MAXM = 50005;

struct Edge {
	int to;
	int next;
	Edge(int tto=0, int tn=0) : to(tto), next(tn) {}
} E[MAXM], oE[MAXM];
int nE, V[MAXN], onE, oV[MAXN];
int f[MAXN], of[MAXN];
bool vis[MAXN];

void addEdge(int V[], Edge E[], int &nE, int u, int v) {
	E[nE] = Edge(v, V[u]);
	V[u] = nE++;
}

void dfs(int V[], Edge E[], int f[], int u) {
	if (vis[u]) return;
	vis[u] = true;
	if (V[u] == -1) {
		f[u] = 1;
		return;
	}
	for (int i = V[u]; i != -1; i = E[i].next) {
		if (false == vis[E[i].to]) {
			dfs(V, E, f, E[i].to);
		}
		f[u] += f[E[i].to];
	}
}

int main()
{
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		memset(V, -1, sizeof(V));
		memset(oV, -1, sizeof(oV));
		nE = 0;
		onE = 0;
		for (int i = 0, a, b; i < m; ++i) {
			scanf("%d%d", &a, &b);
			addEdge(V, E, nE, a, b);
			addEdge(oV, oE, onE, b, a);
		}
		memset(f, 0, sizeof(f));
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; ++i) {
			if (false == vis[i]) {
				dfs(V, E, f, i);
			}
		}
		memset(of, 0, sizeof(of));
		memset(vis, 0, sizeof(vis));
		dfs(oV, oE, of, n);
		int ans = 0;
		for (int i = 1, t; i <= n; ++i) {
			for (int j = V[i]; j != -1; j = E[j].next) {
				t = of[i] * f[E[j].to];
				if (ans < t) ans = t;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

