#include <cstdio>
#include <cstring>
#include <climits>
#include <cmath>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

const int NN = 100001;
const int MM = 1000001;
struct Edge {
	int v;
	struct Edge* next;
};
int nE, n, m;
Edge *head[NN];
Edge E[MM*2];
pair<int, int> conn[MM];
long long sum, son[NN], cnt[NN];
long long ans;

long long llabs(long long a)
{
	return a < 0 ? -a : a;
}

void addEdge(int u, int v)
{
	E[nE].v = v;
	E[nE].next = head[u];
	head[u] = E + nE;
	++nE;
}

void dfs(int p, int pr)
{
	cnt[p] = son[p];
	for (Edge *e = head[p]; e; e = e->next) {
		int c = e->v;
		if (c == pr) continue;
		dfs(c, p);
		cnt[p] += cnt[c];
	}
	long long t = llabs(sum - cnt[p] - cnt[p]);
	if (ans > t) {
		ans = t;
	}
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d", &n, &m) && n > 0 && m > 0) {
		sum = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", son + i);
			sum += son[i];
		}
		memset(head, 0, sizeof(head));
		nE = 0;
		for (int i = 0; i < m; ++i) {
			int u, v, t;
			scanf("%d %d", &u, &v);
			addEdge(u, v);
			addEdge(v, u);
			/*
			if (u > v) {t = u; u = v; v = t;}
			conn[i].first = u;
			conn[i].second = v;
			*/
		}
		/*
		sort(conn, conn + m);
		int j = 0;
		for (int i = 1; i < m; ++i) {
			if (conn[j] != conn[i]) {
				conn[++j] = conn[i];
			}
		}
		m = j + 1;
		for (int i = 0; i < m; ++i) {
			addEdge(conn[i].first, conn[i].second);
			addEdge(conn[i].second, conn[i].first);
		}
		*/
		ans = LLONG_MAX;
		dfs(1, -1);
		printf("Case %d: %lld\n", ++nCase, ans);
	}
	return 0;
}
