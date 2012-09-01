/* Time to live
 * http://www.spoj.pl/problems/GCPC11J/
 * 树的直径，两遍BFS，先从任意一点u找到最远点v，再从v找最远点t,v-t就是直径
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

struct Edge {
	int to;
	Edge *next;
} E[MAXN*2], *V[MAXN];
int n, nE;

void addEdge(int u, int v) {
	Edge *e = E + nE++;
	e->to = v, e->next = V[u];
	V[u] = e;
}

int q[MAXN];
int dis[MAXN];
int bfs(int u) {
	int fr = 0, ta = 0;
	int v = u, len = 0;
	for (int i = 0; i < n; ++i) dis[i] = n;
	dis[u] = 0;
	q[ta++] = u;
	while (fr < ta) {
		u = q[fr++];
		for (Edge *e = V[u]; e; e = e->next) {
			if (dis[e->to] < n) continue;
			dis[e->to] = dis[u] + 1;
			q[ta++] = e->to;
			if (len < dis[e->to]) {
				len = dis[e->to];
				v = e->to;
			}
		}
	}
	return v;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d", &n);
		memset(V, 0, sizeof(V));
		nE = 0;
		for (int i = 1, a, b; i < n; ++i) {
			scanf("%d%d", &a, &b);
			addEdge(a, b);
			addEdge(b, a);
		}
		int v = bfs(0);
		v = bfs(v);
		printf("%d\n", (dis[v] / 2) + (dis[v] % 2));
	}
	return 0;
}
