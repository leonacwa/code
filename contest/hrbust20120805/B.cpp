/* March of the Penguins
 * */
#include <cstdio>
#include <cstring>
#include <climits>

const int INF = INT_MAX / 3;
const int MAXN = 205;
const int MAXM = 205 * 205 * 4;

struct Edge {
	int u, v;
	int c;
	int next;
	Edge() {}
	Edge(int tu, int tv, int tc, int tn) : u(tu), v(tv), c(tc), next(tn) {}
};

Edge E[MAXM], bE[MAXM];
// head[]���㻡���ͷ
int nE, head[MAXN], cnt[MAXN], que[MAXN], d[MAXN], low[MAXN], cur[MAXN];

void addEdge(int u, int v, int c, int rc = 0) { // c ����������rc��������
	E[nE]= Edge(u, v, c, head[u]);
	head[u] = nE++;
	E[nE]= Edge(v, u, rc, head[v]);
	head[v] = nE++;
}

void initNetwork(int n = -1) { // head[] �����ʼ��Ϊ-1
	if (n == -1) n = MAXN;
	memset(head, -1, sizeof(head[0])*MAXN);
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
	while (d[source] < n) { // que������pre���飬����Ǳ�
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

struct Point  {
	double x, y;
	int n, m;
} pt[MAXN];

double sq(double x) {
	return x * x;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, source, tot, sum = 0;
		double max_jump;
		scanf("%d%lf", &n, &max_jump);
		source = n + n;
		tot = n + n + 1;
		initNetwork();
		for (int i = 0; i < n; ++i) {
			scanf("%lf%lf%d%d", &pt[i].x, &pt[i].y, &pt[i].n, &pt[i].m);
			sum += pt[i].n;
			addEdge(i, i + n, pt[i].m);
			if (pt[i].n > 0) {
				addEdge(source, i, pt[i].n);
			}
		}
		double d2 = max_jump * max_jump;
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				double dis2 = sq(pt[i].x - pt[j].x) + sq(pt[i].y - pt[j].y);
				if (d2 >= dis2) {
					addEdge(i+n, j, INF);
					addEdge(j+n, i, INF);
				}
			}
		}
		for (int j = 0; j < nE; ++j) bE[j] = E[j];
		bool ans = false;
		for (int i = 0; i < n; ++i) {
			int flow = maxflow(tot, source, i);
			if (flow == sum) {
				if (ans) printf(" ");
				else ans = true;
				printf("%d", i);
			}
			if (i + 1 < n) memcpy(E, bE, sizeof(E[0]) * nE);
		}
		if (false == ans) puts("-1");
		else puts("");
	}
	return 0;
}
