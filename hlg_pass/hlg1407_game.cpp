/* Leyni的游戏
 * KM 算法的应用
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 405, MAXM = 90000, INF = 99999999;

struct Edge {
	int to;
	int w;
	Edge *next;
};
int nE;
Edge *V[MAXN], E[MAXM];
int m1[MAXN], m2[MAXN];
int lx[MAXN], ly[MAXN], slack[MAXN];
int vx[MAXN], vy[MAXN], _FLAG;

int mat[205][205];

void addEdge(int u, int v, int w) {
	Edge *e = E + nE++;
	e->to = v, e->w = w, e->next = V[u];
	V[u] = e;
}

bool KM_dfs(int x) {
	vx[x] = _FLAG;
	for (Edge *e = V[x]; e; e = e->next) {
		int y = e->to;
		if (vy[y] == _FLAG) continue;
		int t = lx[x] + ly[y] - e->w;
		if (t == 0) {
			vy[y] = _FLAG;
			if (m2[y] == -1 || KM_dfs(m2[y])) {
				m2[y] = x;
				m1[x] = y;
				return true;
			}
		} else if (slack[y] > t) {
			slack[y] = t;
		}
	}
	return false;
}

int KM(int n1, int n2) {
	_FLAG = 0;
	for (int i = 0; i < n1; ++i) {
		m1[i] = -1;
		vx[i] = -1;
		lx[i] = -INF;
		for (Edge *e = V[i]; e; e = e->next) {
			if (lx[i] < e->w) lx[i] = e->w;
		}
		//if (lx[i] == -INF) return -1;
	}
	for (int i = 0; i < n2; ++i) {
		m2[i] = -1;
		vy[i] = -1;
		ly[i] = 0;
	}
	for (int i = 0; i < n1; ++i) {
		for (int j = 0; j < n2; ++j) slack[j] = INF;
		++_FLAG;
		while (!KM_dfs(i)) {
			int d = INF;
			for (int j = 0; j < n2; ++j) {
				if (vy[j] != _FLAG && d > slack[j]) d = slack[j];
			}
			if (d == INF) break;
			for (int j = 0; j < n1; ++j) {
				if (vx[j] == _FLAG) lx[j] -= d;
			}
			for (int j = 0; j < n2; ++j) {
				if (vy[j] == _FLAG) ly[j] += d;
			}
			++_FLAG;
		}
	}
	int ret = 0;
	/*
	for (int i = 0; i < n1; ++i) ret += lx[i];
	for (int i = 0; i < n2; ++i) ret += ly[i];
	*/
	for (int i = 0; i < n2; ++i) if (m2[i] != -1) ret += mat[m2[i]][i];
	return ret;
}

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)  scanf("%d", &mat[i][j]);
		int ns = n;
		if (ns < m) ns = m;
		memset(V, 0, sizeof(V));
		nE = 0;
		for (int i = 0; i < ns; ++i) {
			for (int j = 0; j < ns; ++j) {
				addEdge(i, j, mat[i][j]);
			}
		}
		int ans = KM(ns, ns);
		printf("%d\n", ans);
	}
	return 0;
}
