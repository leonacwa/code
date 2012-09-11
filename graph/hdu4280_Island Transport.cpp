/* HDU 4280 Island Transport
 * 最大流水过，其实应该是用对偶图转换，然后用最短路求解
 * */
#include <cstdio>
#include <cstring>
#include <climits>

const int INF = INT_MAX / 2;
const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;

struct Edge {
	int u, v;
	int c;
	int next;
	Edge(int tu=0, int tv=0, int tc=0, int tn=0) : u(tu), v(tv), c(tc), next(tn) {}
};

Edge E[MAXM * 3];
int nE, head[MAXN], cnt[MAXN], que[MAXN], d[MAXN], low[MAXN], cur[MAXN];

void addEdge(int u, int v, int c, int rc = 0) {
	E[nE]= Edge(u, v, c, head[u]);
	head[u] = nE++;
	E[nE]= Edge(v, u, rc, head[v]);
	head[v] = nE++;
}

void initNetwork(int n = MAXN) {
	memset(head, -1, sizeof(head[0])*n);
	nE = 0;
}

int maxflow(int n, int source, int sink) {
	int *fr = que, *ta = que;;
	for (int i = 0; i < n; ++i) d[i] = n, cnt[i] = 0;
	cnt[n] = n - 1, cnt[0]++, d[sink] = 0;
	*ta++ = sink;
	while (fr < ta) {
		int v = *fr++;
		for (int i = head[v]; i != -1; i = E[i].next) {
			if (d[E[i].v] == n && E[i^1].c > 0) {
				d[E[i].v] = d[v] + 1;
				cnt[n]--;
				cnt[d[E[i].v]]++;
				*ta++ = E[i].v;
			}
		}
	}
	int flow = 0, u = source, top = 0;
	low[0] = INF;
	for (int i = 0; i < n; ++i) cur[i] = head[i];
	while (d[source] < n) {
		int &i = cur[u];
		for (; i != -1; i = E[i].next) {
			if (E[i].c > 0 && d[u] == d[E[i].v] + 1) {
				low[top+1] = low[top] < E[i].c ? low[top] : E[i].c;
				que[top+1] = i;
				++top;
				u = E[i].v;
				break;
			}
		}
		if (i != -1) {
			if (u == sink) {
				int delta = low[top];
				for (int p = 1, i; p <= top; ++p) {
					i = que[p];
					E[i].c -= delta;
					E[i^1].c += delta;
				}
				flow += delta;
				u = source;
				low[0] = INF;
				top = 0;
			}
		} else {
			int old_du = d[u];
			cnt[old_du]--;
			d[u] = n - 1;
			for (int i = head[u]; i != -1; i = E[i].next) {
				if (E[i].c > 0 && d[u] > d[E[i].v]) d[u] = d[E[i].v];
			}
			cnt[++d[u]]++;
			if (d[u] < n) cur[u] = head[u];
			if (u != source) {
				u = E[que[top]].u;
				--top;
			}
			if (cnt[old_du] == 0) break;
		}
	}
	return flow;
}
struct Point {
	int x,y;
} p[100005];

template <class T>
int scan_i(T &x) {
	int ch;
	bool ne = false;
	while (EOF != (ch = getchar()) && ('0' > ch || ch > '9') && ch != '-') ;
	if (EOF == ch) return EOF;
	if (ch == '-') {
		ne = 1;
		ch = getchar();
	}
	x = 0;
	while ('0' <= ch && ch <= '9') {
		x *= 10;
		x += ch - '0';
		ch = getchar();
	}
	if (ne) x = -x;
	return 1;
}

int main()
{
	int runs;
	//scanf("%d", &runs);
	scan_i(runs);
	while(runs--) {
		int n, m;
	//	scanf("%d%d", &n, &m);
		scan_i(n);
		scan_i(m);
		int sink = 1, source = 1;
		for(int i = 1; i <= n;i++) {
			//scanf("%d%d", &p[i].x, &p[i].y);
			scan_i(p[i].x);
			scan_i(p[i].y);
			if(p[i].x<p[source].x) source = i;
			if(p[i].x>p[sink].x) sink = i;
		}
		initNetwork(n+1);
		while(m--) {
			int a, b, c;
			//scanf("%d%d%d", &a, &b, &c);
			scan_i(a);
			scan_i(b);
			scan_i(c);
			addEdge(a-1, b-1, c);
			addEdge(b-1, a-1, c);
		}
		printf("%d\n",maxflow(n, source-1, sink-1));
	}
	return 0;
}
