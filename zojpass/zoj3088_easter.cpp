#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <queue>
using namespace std;
const int NN = 1001;
const int MM = 1001;
struct Edge {
	int v, w;
	Edge * next;
};
int nE[2];
Edge E[2][MM];
Edge * head[2][NN];

int len[2][NN][NN], prev[2][NN][NN];
int a[NN*2];

void addEdge(Edge *head[NN], Edge E[NN], int &nE, int u, int v, int w)
{
	Edge *e = E + nE++;
	e->v = v;
	e->w = w;
	e->next = head[u];
	head[u] = e;
}

bool inq[NN];
int cnt[NN];

void SPFA(int n, int s, Edge *head[NN], Edge E[NN], int nE, int len[NN], int prev[NN], bool isMin)
{
	for (int i = 0; i <= n; ++i) {
		len[i] = isMin ? INT_MAX : -INT_MAX;
		prev[i] = -1;
	}
	len[s] = 0;
	prev[s] = -1;
	memset(inq, 0, sizeof(inq[0]) * (n + 1));
	memset(cnt, 0, sizeof(cnt[0]) * (n + 1));
	inq[s] = true;
	queue<int> Q;
	Q.push(s);
	cnt[s]++;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		inq[u] = false;
		for (Edge *e = head[u]; e; e = e->next) {
			if (isMin == (len[u] + e->w < len[e->v])) {
				len[e->v] = len[u] + e->w;
				prev[e->v] = u;
				if (!inq[e->v]) {
					Q.push(e->v);
					cnt[e->v]++;
					inq[e->v] = true;
				}
			}
		}
	}
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, m, k;
		scanf("%d %d %d", &n, &m, &k);
		nE[0] = nE[1]  = 0;
		memset(head, 0, sizeof(head));
		int u, v, w;
		for (int i = 0; i < m; ++i) { // Slopes
			scanf("%d %d %d", &u, &v, &w);
			addEdge(head[0], E[0], nE[0], u, v, w);
		}
		for (int i = 0; i < k; ++i) { // lifta
			scanf("%d %d %d", &u, &v, &w);
			addEdge(head[1], E[1], nE[1], u, v, w);
		}
		for (int i = 1; i <= n; ++i) {
			SPFA(n, i, head[0], E[0], nE[0], len[0][i], prev[0][i], false);
			SPFA(n, i, head[1], E[1], nE[1], len[1][i], prev[1][i], true);
		}
		double ans = -2;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i == j || len[0][i][j] == INT_MAX || len[1][j][i] == INT_MAX) continue;
				double t = (double)len[0][i][j] / len[1][j][i];
				if (t > ans) {
					ans = t;
					u = i;
					v = j;
				}
			}
		}
		int p = u;
		int a_cnt = 0;
		while (p != -1) {
			a[a_cnt++] = p;
			p = prev[1][v][p];
		}
		printf("%d", a[a_cnt-1]);
		for (int i = a_cnt - 2; i >= 0; --i) {
			printf(" %d", a[i]);
		}
		p = v;
		a_cnt = 0;
		while (p != -1) {
			a[a_cnt++] = p;
			p = prev[0][u][p];
		}
		for (int i = a_cnt - 2; i >= 0; --i) {
			printf(" %d", a[i]);
		}
		printf("\n%.3f\n", ans);
	}
	return 0;
}

