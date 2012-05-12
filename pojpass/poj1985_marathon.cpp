#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 40000 + 1;

struct Edge {
	int v, len;
	Edge *next;
};
int nE, n, m;
Edge *head[NN];
Edge E[2*NN];
int ans;

void addEdge(int u, int v, int len)
{
	E[nE].v = v;
	E[nE].len = len;
	E[nE].next = head[u];
	head[u] = E + nE;
	++nE;
}

int dfs(int p, int pr)
{
	int sum = 0;
	while (1) {
		int cnt = 0;
		for (Edge *e = head[p]; e; e = e->next) {
			if (pr == e->v) continue;
			++cnt;
			if (cnt > 1) break;
		}
		if (cnt == 0) return sum;
		if (cnt > 1) break;
		for (Edge *e = head[p]; e; e = e->next) {
			if (pr == e->v) continue;
			sum += e->len;
			pr = p;
			p = e->v;
			break;
		}
	}
	int maxlen = 0;
	int ret = 0;
	for (Edge *e = head[p]; e; e = e->next) {
		if (pr == e->v) continue;
		int clen = dfs(e->v, p);
		int t = sum + e->len + clen;
		if (ret < t) ret = t;
		t = clen + e->len;
		if (ans < maxlen + t)  ans = maxlen + t;
		if (maxlen < t) maxlen = t;
	}
	return ret;
}

int main()
{
	while (EOF != scanf("%d %d", &n, &m)) {
		nE = 0;
		memset(head, 0, sizeof(head));
		for (int i = 0; i < m; ++i) {
			int u, v, len, d;
			scanf("%d %d %d %c", &u, &v, &len, &d);
			addEdge(u, v, len);
			addEdge(v, u, len);
		}
		ans = 0;
		int t = dfs(1, -1);
		if (ans < t) ans = t;
		printf("%d\n", ans);
	}
	return 0;
}
