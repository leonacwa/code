#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 40000 + 5;
struct Edge {
	int to, len;
	Edge * next;
};
int nE;
Edge E[MAXN * 2];
Edge *head[MAXN];
int fir[MAXN];
int seq_cnt;
int seq[MAXN * 2];
int dep[MAXN * 2];
int Min[MAXN * 2][20];

void addEdge(int u, int v, int len)
{
	Edge *e = E + nE++;
	e->to = v;
	e->len = len;
	e->next = head[u];
	head[u] = e;
}

void dfs(int p, int pr, int depth)
{
	seq[seq_cnt] = p;
	dep[seq_cnt] = depth;
	if (fir[p] == -1) {
		fir[p] = seq_cnt;
	}
	seq_cnt++;
	for (Edge *e = head[p]; e; e = e->next) {
		if (e->to == pr) continue;
		dfs(e->to, p, depth + e->len);
		seq[seq_cnt] = p;
		dep[seq_cnt] = depth;
		seq_cnt++;
	}
}

void RMQ_init(int n)
{
	int nn = n * 2 - 1; //seq_cnt; //n * 2;
	for (int i = 0; i < nn; ++i) {
		Min[i][0] = i;
	}
	for (int j = 1; (1 << j) <= nn; ++j) {
		for (int i = 0; i + (1<<j) - 1 < nn; ++i) {
			if (dep[Min[i][j-1]] < dep[Min[i+(1 << (j-1))][j-1]]) {
				Min[i][j] = Min[i][j-1];
			} else {
				Min[i][j] = Min[i+(1 << (j-1))][j-1];
			}
		}
	}
}

int RMQ_query(int l, int r)
{
	int j = 0;
	for (; (1 << j) <= r - l + 1; ++j) ;
	--j;
	if (dep[Min[l][j]] < dep[Min[r-(1<<j)+1][j]]) {
		return Min[l][j];
	} else {
		return Min[r-(1<<j)+1][j];
	}
}

int main()
{
	int n, m;
	while (EOF != scanf("%d %d", &n, &m)) {
		nE = 0;
		memset(head, 0, sizeof(head));
		for (int i = 0; i < m; ++i) {
			int a, b, l;
			scanf("%d %d %d %*s", &a, &b, &l);
			addEdge(a, b, l);
			addEdge(b, a, l);
		}
		memset(fir, -1, sizeof(fir));
		seq_cnt = 0;
		dfs(1, 0, 0);
		RMQ_init(n);
		int k;
		scanf("%d", &k);
		while (k--) {
			int a, b;
			scanf("%d %d", &a, &b);
			if (fir[a] > fir[b]) {
				swap(a, b);
			}
			int fa = fir[a], fb = fir[b];
			int lca = RMQ_query(fa, fb);
			printf("%d\n", dep[fa] + dep[fb] - 2 * dep[lca]);
		}
	}
	return 0;
}

