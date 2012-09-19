/* HDU 4297 One and One Story
 * 森林的LCA，利用题目数据的特殊性：有向图、每个点出度仅为1
 * 画出图后，发现有些点能通过一些路径次回到自己，即有环，那么把环上的点作为根，并把所有的构成环的边去掉，这样就形成一个又一个树，这些树构成森林。
 * 对于询问 a b, 然后分三种情况考虑：
 * 1.如果a, b在同一个树上，即树根相同，则为LCA问题。
 * 2.如果a, b不在同一个树上，并且a和b的树根不在环上，输出-1 -1
 * 3.如果a, b不在同一个树上，但是a和b的树根在环上，，那么分别比较从a走到b和b走到a两种情况，取最优解即可。
 * */
#pragma comment(linker, "/STACK:102400000,102400000") 
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define noDEBUG

const int MAXN = 5000001;

struct Arc {
	int to;
	Arc *next;
};
Arc A[MAXN * 2], *V[MAXN];
int nA;

void addArc(int u, int v) {
	Arc *a = A + nA++;
	a->to = v, a->next = V[u];
	V[u] = a;
}

// LCA RMQ
int seq[MAXN * 2], dep[MAXN], fir[MAXN];
int rmq[20][MAXN * 2];
int seq_cnt;

int dest[MAXN];
int root[MAXN];
int pos[MAXN];
int cc[MAXN], cnt[MAXN];
int cc_cnt;
int fa[MAXN];

int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}

void rmq_init() {
	int n = seq_cnt;
	for (int i = 0; i < n; ++i) rmq[0][i] = seq[i];
	for (int l = 0; (1<<(l+1)) <= n; ++l) {
		int limit = n - (1<<(l+1));
		for (int i = 0, t; i < limit; ++i) {
			if (dep[rmq[l][i]] < dep[rmq[l][i+(1<<l)]]) t = rmq[l][i];
			else t = rmq[l][i+(1<<l)];
			rmq[l+1][i] = t;
			while(l+1>20) ;
		}
	}
}

int rmq_query(int a, int b) { /* 居然没注意区间的范围的问题，导致一直WA，尼玛*/
	a = fir[a], b =fir[b];
	if (a > b) swap(a, b);
	int l = 0, len = b - a + 1;
	for (; (1<<l) < len; ++l) ;
	if ((1<<l) == len) return rmq[l][a];
	--l;
	while(l>20) ;
	if (dep[rmq[l][a]] < dep[rmq[l][b+1-(1<<l)]]) return rmq[l][a];
	else return rmq[l][b+1-(1<<l)];
}

void lca_tarjan(int u, int dpt) {
	fir[u] = seq_cnt;
	seq[seq_cnt++] = u;
	dep[u] = dpt;
	for (Arc *a = V[u]; a; a = a->next) {
		if (dep[a->to] != -1) continue;
		lca_tarjan(a->to, dpt+1);
		seq[seq_cnt++] = u;
	}
}

void find_loop(int n) {
	for (int i = 0; i <= n; ++i) fa[i] = i;
	cc_cnt = 0;
	memset(root, -1, sizeof(root));
	memset(cc, -1, sizeof(cc));
	memset(pos, -1, sizeof(pos));
	for (int i = 1; i <= n; ++i) {
		int a = find(i), b = find(dest[i]);
		if (a == b) {
			cc[i] = cc_cnt++;
			root[i] = i;
			pos[i] = 0;
		}
		fa[a] = b;
	}
	for (int i = 1; i <= n; ++i) {
		if (pos[i] == 0) {
			int c = cc[i];
			int lc = 1;
			int k = dest[i];
			while (k != i) {
				cc[k] = c;
				pos[k] = lc++;
				root[k] = k;
				k = dest[k];
			}
			cnt[c] = lc;
		}
	}
	for (int i = 0; i <= n; ++i) fa[i] = i;
	for (int i = 1; i <= n; ++i) {
		if (root[i] == i && root[dest[i]] == dest[i]) continue;
		fa[i] = dest[i];
	}
}

int main() {
	int n, k;
	while (EOF != scanf("%d%d", &n, &k)) {
		for (int i = 1; i <= n; ++i) scanf("%d", &dest[i]);
		find_loop(n);
		memset(V, 0, sizeof(V));
		nA = 0;
		for (int i = 1; i <= n; ++i) {
			if (root[i] != i) {
				addArc(dest[i], i);
				//addArc(i, dest[i]);
			} else {
				addArc(0, i);
				//addArc(i, 0);
			}
		}
		seq_cnt = 0;
		memset(dep, -1, sizeof(dep));
		lca_tarjan(0, 0);
		rmq_init();
		while (k--) {
			int a, b;
			scanf("%d%d", &a, &b);
			int x = find(a), y = find(b);
#ifdef DEBUG
			printf("query %d %d\n", a, b);
			printf("%d:%d %d\n", a, x, dep[a] - dep[x]);
			printf("%d:%d %d\n", b, y, dep[b] - dep[y]);
#endif
			if (x == y) {
				int f = rmq_query(a, b);
				while (f <= 0);
#ifdef DEBUG
				printf("f %d %d: %d\n", a, b, f);
#endif
				printf("%d %d\n", dep[a] - dep[f], dep[b] - dep[f]);
			} else if (cc[x] != cc[y]) {
				puts("-1 -1");
			} else {
				int la1, lb1, la2, lb2, t;
				la1 = la2 = dep[a] - dep[x];
				lb1 = lb2 = dep[b] - dep[y];
				if (pos[x] < pos[y]) {
					la1 += pos[y] - pos[x];
					lb2 += cnt[cc[x]] - (pos[y] - pos[x]);
				} else {
					la1 += cnt[cc[x]] - (pos[x] - pos[y]);
					lb2 += pos[x] - pos[y];
				}
				t = max(la1, lb1) - max(la2, lb2);
				if (t == 0) {
					t = min(la1, lb1) - min(la2, lb2);
					if (t == 0) {
						if (la1 >= lb1) t = -1;
						else t = 1;
					}
				}
				if (t < 0) printf("%d %d\n", la1, lb1);
				else printf("%d %d\n", la2, lb2);
			}
		}
#ifdef DEBUG
		puts("");
#endif
	}
	return 0;
}
