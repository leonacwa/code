#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 100000 + 5;

int n, q, s;

struct Edge {
	int to, len;
	Edge * next;
};
int nE;
Edge *head[MAXN];
Edge E[MAXN * 2];

void addEdge(int u, int v, int len)
{
	Edge *e = E + nE++;
	e->to = v;
	e->len = len;
	e->next = head[u];
	head[u] = e;
}

int C[MAXN * 2];

int lowbit(int x) {
	return x & (-x);
}

void add(int x, int delta) {
	for (; x < (n<<1); x += lowbit(x)) {
		C[x] += delta;
	}
}

int sum(int x) {
	int ret = 0;
	for (; x > 0; x -= lowbit(x)) {
		ret += C[x];
	}
	return ret;
}

int seq_cnt;
int seq[MAXN * 2];
int H[MAXN];
int R[MAXN];
int len[MAXN * 2];

void dfs(int p, int pr, int length)
{
	seq_cnt++;
	seq[seq_cnt] = p;
	len[seq_cnt] = length;
	if (H[p] == -1) {
		H[p] = seq_cnt;
	}
	for (Edge *e = head[p]; e; e = e->next) {
		if (e->to == pr) continue;
		dfs(e->to, p, length + e->len);
		seq_cnt++;
		seq[seq_cnt] = p;
		len[seq_cnt] = length;
	}
	R[p] = seq_cnt;
}

int Min[MAXN * 2][20];

void init_rmq()
{
	int nn = 2 * n - 1;
	for (int i = 1; i <= nn; ++i) {
		Min[i][0] = i;
	}
	for (int j = 1; 1 << j <= nn; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= nn; ++i) {
			if (len[Min[i][j-1]] < len[Min[i+(1<<(j-1))][j-1]]) {
				Min[i][j] = Min[i][j-1];
			} else {
				Min[i][j] = Min[i+(1<<(j-1))][j-1];
			}
		}
	}
}

int query_rmq(int l, int r)
{
	int j;
	for (j = 0; 1 << j <= r - l + 1; ++j) ;
	--j;
	if (len[Min[l][j]] < len[Min[r-(1<<j)+1][j]]) {
		return Min[l][j];
	} else {
		return Min[r-(1<<j)+1][j];
	}
}

struct LinkPath {
	int u, v, len;
};
LinkPath path[MAXN];

int main()
{
	while (EOF != scanf("%d %d %d", &n, &q, &s)) {
		nE = 0;
		memset(head, 0, sizeof(head));
		
		for (int i = 1; i < n; ++i) {
			int u, v, l;
			scanf("%d %d %d", &u, &v, &l);
			path[i].u = u;
			path[i].v = v;
			path[i].len = l;
			addEdge(u, v, l);
			addEdge(v, u, l);
		}

		seq_cnt = 0;
		memset(H, -1, sizeof(H));
		dfs(1, 0, 0);
		init_rmq();
		memset(C, 0, sizeof(C));
		for (int i = 0; i < q; ++i) {
			int m, a, l;
			scanf("%d", &m);
			if (0 == m) {
				scanf("%d", &a);
				int fa = H[a], fs = H[s];
				if (fs > fa) {
					swap(fs, fa);
				}
				int lca = query_rmq(fs, fa);
				printf("%d\n", len[fs] + len[fa] - 2 * len[lca] + sum(H[s]) + sum(H[a]) - 2 * sum(H[seq[lca]]));
				s = a;
			} else {
				scanf("%d %d", &a, &l);
				int u = path[a].u, v = path[a].v;
				if (H[u] > H[v]) {
					swap(u, v);
				}
				int delta = l - path[a].len;
				path[a].len = l;
				add(H[v], delta); 
				add(R[v]+1, -delta);
			}
		}
	}
	return 0;
}

