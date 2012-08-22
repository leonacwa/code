/*
 * bfs
 * */
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
int Q[NN];
int front, tail;
int len[NN];

void addEdge(int u, int v, int len)
{
	E[nE].v = v;
	E[nE].len = len;
	E[nE].next = head[u];
	head[u] = E + nE;
	++nE;
}

int bfs(int s)
{
	int k = s;
	memset(len, -1, sizeof(len));
	front = 0;
	tail = 0;
	Q[0] = s;
	len[s] = 0;
	while (front <= tail) {
		int u = Q[front++];
		if (len[k] < len[u]) {
			k = u;
		}
		for (Edge *e = head[u]; e; e = e->next) {
			if (-1 == len[e->v]) {
				len[e->v] = len[u] + e->len;
				Q[++tail] = e->v;
			}
		}
	}
	return k;
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
		int s = bfs(1);
		int t = bfs(s);
		printf("%d\n", len[t]);
	}
	return 0;
}

