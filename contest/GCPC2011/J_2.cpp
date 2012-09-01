/* Time to live
 * http://www.spoj.pl/problems/GCPC11J/
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
int nE;

void addEdge(int u, int v) {
	Edge *e = E + nE++;
	e->to = v, e->next = V[u];
	V[u] = e;
}

int left, right, left_len, right_len;
bool vis[MAXN];
int P[MAXN];
int vlist_size;
int vlist[MAXN];
int vson[MAXN];
int vlen[MAXN];

void dfs(int u, int &son, int &son_len) {
	int son2 = u, son2_len = 0, t, tmax;
	son_len = 0;
	son = u;
	vis[u] = true;
	for (Edge *e = V[u]; e; e = e->next) {
		if (vis[e->to]) continue;
		P[e->to] = u;
		dfs(e->to, t, tmax);
		++tmax;
		if (son_len < tmax) {
			son2 = son, son2_len = son_len;
			son = t, son_len = tmax;
		} else if (son2_len < tmax) {
			son2 = t, son2_len = tmax;
		}
	}
	if (left_len + right_len < son_len + son2_len) {
		left = son, right = son2, left_len = son_len, right_len = son2_len;
	}
}

void dfs_len(int u, int &son, int &son_len) {
	int t, tmax;
	son = u;
	son_len = 0;
	vis[u] = true;
	for (Edge *e = V[u]; e; e = e->next) {
		if (vis[e->to]) continue;
		dfs_len(e->to, t, tmax);
		++tmax;
		if (son_len < tmax) {
			son = t, son_len = tmax;
		}
	}
}

int get_len(int x) {
	int tmax = 0, ret = 0;
	for (int i = 0; i < vlist_size; ++i) {
		tmax = abs(x - i) + vlen[i];
		if (ret < tmax) ret = tmax;
	}
	return ret;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n;
		scanf("%d", &n);
		memset(V, 0, sizeof(V));
		nE = 0;
		for (int i = 1, a, b; i < n; ++i) {
			scanf("%d%d", &a, &b);
			addEdge(a, b);
			addEdge(b, a);
		}
		left = right = 0;
		left_len = right_len = 0;
		int t, tmax;
		memset(vis, 0, sizeof(vis));
		dfs(0, t, tmax);
		memset(vis, 0, sizeof(vis));
		vlist_size = left_len + right_len + 1;
		int p = left;
		for (int i = 0; i < left_len; ++i) {
			vis[p] = true;
			vlist[i] = p; 
			p = P[p];
		}
		vis[p] = true;
		vlist[left_len] = p; 
		t = vlist_size - 1;
		p = right;
		for (int i = 0; i < right_len; ++i) {
			vis[p] = true;
			vlist[t--] = p;
			p = P[p];
		}
		for (int i = 0; i < vlist_size; ++i) {
			dfs_len(vlist[i], vson[i], vlen[i]);
		}
		int l = 0,  r = vlist_size - 1;
		while (l < r-2) {
			int m1 = (2*l + r) / 3;
			int m2 = (l + 2*r) / 3;
			if (get_len(m1) <= get_len(m2)) {
				r = m2;
			} else {
				l = m1;
			}
		}
		int ans = min(get_len(l), get_len(r));
		if (l+1 < r) {
			ans = min(ans, get_len(l+1));
		}
		printf("%d\n", ans);
	}
	return 0;
}
