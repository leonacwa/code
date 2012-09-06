/* hdu 4008 Parent and son
 * http://acm.hdu.edu.cn/showproblem.php?pid=4008
 * 树形DP
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXM = 200005, MAXN = 100005, INF = 99999999;

struct Arc {
	int to;
	Arc *next;
} A[MAXM], *V[MAXN];
int nA;

struct SD {
	int s1, s2, c1, c2, f;
} ans[MAXN];

int dfn[MAXN], maxdfn[MAXN];
int P[MAXN];
int order;

template <class T>
void check_max(T &a, const T &b) {
	if (a < b) a = b;
}

int read_num(int *x) {
	int ch;
	while (EOF != (ch = getchar()) && ('0' > ch || ch > '9')) ;
	if (EOF == ch) return EOF;
	*x = 0;
	while ('0' <= ch && ch <= '9') {
		*x *= 10;
		*x += ch - '0';
		ch = getchar();
	}
	return 1;
}
void addArc(int u, int v) {
	Arc *a = A + nA++;
	a->to = v, a->next = V[u];
	V[u] = a;
}

void dfs(int u, int pu) {
	dfn[u] = maxdfn[u] = ++order;
	P[u] = pu;
	ans[u].s1 = ans[u].s2 = ans[u].c1 = ans[u].c2 = ans[u].f = INF;
	for (Arc *a = V[u]; a; a = a->next) {
		if (pu == a->to) continue;
		int v = a->to;
		dfs(v, u);
		check_max(maxdfn[u], maxdfn[v]);
		if (v < ans[u].s1) {
			ans[u].s2 = ans[u].s1;
			ans[u].s1 = v;
		} else if (v < ans[u].s2) {
			ans[u].s2 = v;
		}
		int t = min(v, ans[v].c1);
		if (t < ans[u].c1) {
			ans[u].c2 = ans[u].c1;
			ans[u].c1 = t;
			ans[u].f = v;
		} else if (t < ans[u].c2) {
			ans[u].c2 = t;
		}
	}
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, q;
		scanf("%d%d", &n, &q);
		memset(V, 0, sizeof(V));
		nA = 0;
		for (int i = 1, a, b; i < n; ++i) {
			//scanf("%d%d", &a, &b);
			read_num(&a);
			read_num(&b);
			addArc(a, b);
			addArc(b, a);
		}
		order = 0;
		dfs(1, INF);
		while (q--) {
			int x, y, a = INF, b = INF;
			scanf("%d%d", &x, &y);
			if (dfn[x] < dfn[y] || dfn[x] > maxdfn[y]) { // x 作为 y的祖先
				a = ans[y].s1, b = ans[y].c1;
			} else { // x 作为y的子树
				a = (dfn[ans[y].s1]<=dfn[x]&&dfn[x]<=maxdfn[ans[y].s1]) ? ans[y].s2 : ans[y].s1;
				b = (dfn[ans[y].f ]<=dfn[x]&&dfn[x]<=maxdfn[ans[y].f ]) ? ans[y].c2 : ans[y].c1;
				if (y != 1) a = min(a, P[y]), b = min(b, 1);
			}
			if (a == INF) puts("no answers!");
			else printf("%d %d\n", a, b);
		}
		puts("");
	}
	return 0;
}
