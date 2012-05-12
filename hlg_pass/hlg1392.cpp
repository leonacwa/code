#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MM = 40;
const int NN = 300;

int m, n, c, mn;
int g[NN][NN];

struct Edge {
	int v;
	Edge *next;
};
int nE;
Edge * head[NN];
Edge E[NN*NN];
bool vis[NN];
int cnt[MM];
int match[MM][NN];

void addEdge(int u, int v)
{
	Edge * e = E + nE++;
	e->v = v;
	e->next = head[u];
	head[u] = e;
}

bool find(int x)
{
	for (Edge *e = head[x]; e; e = e->next) {
		int v = e->v;
		if (!vis[v]) {
			vis[v] = true;
			if (cnt[v] < c) {
				match[v][cnt[v]++] = x;
				return true;
			}
			for (int i = 0; i < c; ++i) {
				if (find(match[v][i])) {
					match[v][i] = x;
					return true;
				}
			}
		}
	}
	return false;
}

bool check(int len)
{
	nE = 0;
	memset(head, 0, sizeof(head));
	for (int i = m; i < mn; ++i) {
		for (int j = 0; j < m; ++j) {
			if (g[i][j] && g[i][j] <= len) {
				addEdge(i, j);
			}
		}
	}
	int sum = 0;
	memset(cnt, 0, sizeof(cnt));
	for (int i = m; i < mn; ++i) {
		memset(vis, 0, sizeof(vis));
		if (find(i)) {
			++sum;
		}
	}
	return sum == n;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d %d", &m, &n, &c);
		mn = m + n;
		for (int i = 0; i < mn; ++i) {
			for (int j = 0; j < mn; ++j) {
				scanf("%d", &g[i][j]);
			}
		}
		for (int k = 0; k < mn; ++k) {
			for (int i = 0; i < mn; ++i) {
				for (int j = 0; j < mn; ++j) {
					if (i != j && g[i][k] && g[k][j] && (g[i][j] == 0 || g[i][j] > g[i][k] + g[k][j])) {
						g[i][j] = g[i][k] + g[k][j];
					}
				}
			}
		}
		int lo = 0, hi = 0;
		for (int i = 0; i < mn; ++i) {
			for (int j = 0; j < mn; ++j) {
				if (hi < g[i][j]) {
					hi = g[i][j];
				}
			}
		}
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			if (check(mi)) {
				hi = mi;
			} else {
				lo = mi + 1;
			}
		}
		printf("%d\n", lo);
	}
	return 0;
}

