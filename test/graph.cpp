#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 30;
struct Edge {
	int to, len;
	struct Edge *next;
};
int nE;
Edge *head[NN];
char id_n[NN];
char n_id[256];
Edge E[NN*(NN-1)];

void addEdge(int u, int v, int len)
{
	//printf("ae: %d %d\n", u, v);
	Edge *e = E + nE++;
	e->to = v;
	e->len = len;
	e->next = head[u];
	head[u] = e;
}

void init()
{
	nE = 0;
	memset(head, 0, sizeof(head));
	memset(id_n, 0, sizeof(id_n));
	memset(n_id, -1, sizeof(n_id));
}

bool vis[NN];

void dfs(int u)
{
	printf("%c ", id_n[u]);
	for (Edge *e = head[u]; e; e = e->next) {
		if (vis[e->to]) continue;
		vis[e->to] = true;
		dfs(e->to);
	}
}


void bfs(int s)
{
	bool vis[NN] = {0};
	int Q[NN];
	int front = 0, tail = 1;
	Q[0] = s;
	while (front < tail) {
		int u = Q[front++];
		printf("%c ", id_n[u]);
		for (Edge *e = head[u]; e; e = e->next) {
			if (vis[e->to]) continue;
			vis[e->to] = true;
			Q[tail++] = e->to;
		}
	}
}

int main()
{
	int n, m;
	init();
	scanf("%d %d\n", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%c\n", &id_n[i]);
	//	printf("%d %c\n", i, id_n[i]);
		n_id[id_n[i]] = i;
	}
	for (int i = 0; i < m; ++i) {
		char ca, cb;
		int len;
		scanf("%c %c %d\n", &ca, &cb, &len);
		addEdge(n_id[ca], n_id[cb], len);
	}
	printf("bfs:");
	bfs(0);
	printf("\n");
	printf("dfs:");
	dfs(0);
	printf("\n");
	return 0;
}

