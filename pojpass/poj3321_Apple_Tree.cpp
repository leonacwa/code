#include <stdio.h>
#include <string.h>

const int MAXN = 100000+5;

int N, M;

struct Edge {
	int v, next;
};
Edge edges[MAXN*3];
int es;
int ve[MAXN];
int depth;
bool vis[MAXN];
int low[MAXN], high[MAXN];
bool pick[MAXN];
int c[MAXN];

void add_edge(int u, int v)
{
	edges[es].v = v;
	edges[es].next = ve[u];
	ve[u] = es;
	es++;
}

void dfs(int u)
{
	vis[u] = true;
	low[u] = ++depth;
	for (int i = ve[u]; i != -1; i = edges[i].next) {
		if (false == vis[edges[i].v]) {
			dfs(edges[i].v);
		}
	}
	high[u] = depth;
}

inline int lowbit(int x)
{
	return x & (-x);
}

void add(int x, int v)
{
	for (; x <= N; x += lowbit(x)) {
		c[x] += v;
	}
}

int sum(int x)
{
	int s = 0;
	for (; x > 0; x -= lowbit(x)) {
		s += c[x];
	}
	return s;
}

int main()
{
	while (EOF != scanf("%d", &N)) {
		memset(ve, -1, sizeof(ve));
		es = 0;
		for (int i = 1; i < N; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
		}
		memset(vis, 0, sizeof(vis));
		depth = 0;
		dfs(1);
		for (int i = 1; i <= N; i++) {
			add(i, 1);
			pick[i] = false;
		}
		scanf("%d", &M);
		while(M--) { 
			int x; char c;
			scanf("\n%c %d", &c, &x);
			if (c == 'C') {
				if (pick[x]) {
					add(low[x], 1);
					pick[x] = false;
				} else {
					add(low[x], -1);
					pick[x] = true;
				}
			} else if (c == 'Q') {
				printf("%d\n", sum(high[x]) - sum(low[x]-1));
			}
		}
	}
	return 0;
}

