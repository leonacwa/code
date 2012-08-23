/* Minimum Cost
 * 最小费用最大流
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 115, MAXM = 25600;
const int INF = 99999;

struct Edge {
	int to;
	int c, w;
	int next;
	Edge(int tto=0, int tc=0, int tw=0, int tn=-1) : to(tto), c(tc), w(tw), next(tn) {}
};
Edge E[MAXM];
int nE, V[MAXN]; // nE 边数，V[]顶点的边链表头

int pre[MAXN];
int path[MAXN];
int sp[MAXN]; // 源点到各个点的费用
int que[MAXN]; 
bool inq[MAXN];

void initNetwork(int n = MAXN) {
	memset(V, -1, sizeof(V[0]) * n);
	nE = 0;
}

void addEdge(int u, int v, int c, int w, int rc = 0) { // rc是反向弧的容量
	E[nE] = Edge(v, c, w, V[u]);
	V[u] = nE++;
	E[nE] = Edge(u, rc, -w, V[v]);
	V[v] = nE++;
}

bool SPFA(int n, int source, int sink) {
	int *fr = que, *ta = que;
	for (int i = 0; i < n; ++i) sp[i] = INF, inq[i] = false;
	pre[source] = -1;
	sp[source] = 0;
	*ta++ = source;
	inq[source] = true;
	while (fr != ta) {
		if (fr == que + MAXN) fr = que;
		int u = *fr++;
		// 未添加该优化：LLL, Large Label Last 队首的距离比队列的平均距离大的则移到队尾，否则取出, 50%的速度提高
		inq[u] = false;
		for (int i = V[u], v; i != -1; i = E[i].next) {
			v = E[i].to;
			if (E[i].c > 0 && sp[v] > sp[u] + E[i].w) {
				sp[v] = sp[u] + E[i].w;
				pre[v] = u;
				path[v] = i;
				if (false == inq[v]) {
					/* SLF Smal Label First 距离更短的顶点在队列前，此优化效果非常明显，推荐使用
					 * 也可以使用 LLL, Large Label Last 进行优化
					 * */
					if (fr != ta && sp[*fr] > sp[v]) {
						fr--;
						if (fr < que) fr = que + MAXN - 1;
						*fr = v;
					} else {
						if (ta == que + MAXN) ta = que;
						*ta++ = v;
					}
					inq[v] = true;
				}
			}
		}
	}
	return sp[sink] < INF;
}

int argument(int n, int source, int sink) {
	int delta = INF;
	for (int i = sink, e; pre[i] != -1; i = pre[i]) {
		e = path[i];
		if (delta > E[e].c) delta = E[e].c;
	}
	for (int i = sink, e; pre[i] != -1; i = pre[i]) {
		e = path[i];
		E[e].c -= delta;
		E[e^1].c += delta;
	}
	return delta;
}
// 最小费用最大流
void mincost_maxflow(int n, int source, int sink, int &flow, int &cost) {
	flow = 0, cost = 0;
	while ( SPFA(n, source, sink) ) {
		int delta = argument(n, source, sink);
		flow += delta;
		cost += sp[sink] * delta;
	}
}

int need[MAXN][MAXN], have[MAXN][MAXN], n_sum[MAXN], h_sum[MAXN];

int main() {
	int n, m, k;
	while (EOF != scanf("%d%d%d", &n, &m, &k)) {
		if (n == 0 && m == 0 && k == 0) break;
		memset(n_sum, 0, sizeof(n_sum));
		memset(h_sum, 0, sizeof(h_sum));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < k; ++j) {
				scanf("%d", &need[i][j]);
				n_sum[j] += need[i][j];
			}
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < k; ++j) {
				scanf("%d", &have[i][j]);
				h_sum[j] += have[i][j];
			}
		}
		bool can = true;
		for (int i = 0; i < k; ++i) {
			if (h_sum[i] < n_sum[i]) {
				can = false;
				break;
			}
		}
		int cost, flow, ans = 0;
		int source = n+m, sink = n+m+1;
		for (int c = 0, w; c < k; ++c) {
			if (can) initNetwork(n+m+2);
			for (int a = 0; a < n; ++a) {
				for (int b = 0; b < m; ++b) {
					scanf("%d", &w);
					if (can) addEdge(b, m+a, INF, w);
				}
			}
			if (!can) continue;
			for (int i = 0; i < m; ++i) {
				addEdge(source, i, have[i][c], 0);
			}
			for (int i = 0; i < n; ++i) {
				addEdge(m+i, sink, need[i][c], 0);
			}
			mincost_maxflow(n+m+2, source, sink, flow, cost);
			ans += cost;
		}
		if (can) {
			printf("%d\n", ans);
		} else {
			puts("-1");
		}
	}
	return 0;
}
