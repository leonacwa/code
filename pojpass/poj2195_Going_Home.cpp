/* POJ 2195 Going Home
 * KM算反 完备匹配下的最大权匹配
 * */
#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <algorithm>
using namespace std;
using namespace rel_ops;
const int INF = INT_MAX;
const int ROW_SIZE = 105, COL_SIZE = 105;
const int MAXN = 10005, MAXM = 1000005;

typedef pair<int, int> PII;
int m_size, h_size;
PII men[ROW_SIZE * COL_SIZE], house[ROW_SIZE * COL_SIZE];
char ma[ROW_SIZE][COL_SIZE];

struct Edge {
	int to;
	int w;
	Edge *next;
};
int nE;
Edge E[MAXM], *V[MAXN];

int m1[MAXN], m2[MAXN], lx[MAXN], ly[MAXN], slack[MAXN];
int vx[MAXN], vy[MAXN];

void addEdge(int u, int v, int w) {
	Edge *e = E + nE++;
	e->to = v, e->w = w, e->next = V[u];
	V[u] = e;
}

int _FLAG;
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
		} else {
			if (slack[y] > t) slack[y] = t;
		}
	}
	return false;
}

int KM(int n1, int n2) { // 完备匹配，n1 <= n2
	_FLAG = 0;
	for (int i = 0; i < n1; ++i) {
		m1[i] = -1;
		vx[i] = -1;
		lx[i] = -INF;
		for (Edge *e = V[i]; e; e = e->next) {
			if (lx[i] < e->w) lx[i] = e->w;
		}
		if (lx[i] == -INF) return -1;
	}
	for (int i = 0; i < n2; ++i) {
		ly[i] = 0;
		vy[i] = -1;
		m2[i] = -1;
	}
	for (int i = 0; i < n1; ++i) {
		for (int j = 0; j < n2; ++j) slack[j] = INF;
		++_FLAG;
		while (!KM_dfs(i)) {
			int d = +INF;
			for (int j = 0; j < n2; ++j) {
				if (vy[j] != _FLAG && d > slack[j]) d = slack[j];
			}
			if (d == INF) return -1;
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
	for (int i = 0; i < n1; ++i) ret += lx[i];
	for (int i = 0; i < n2; ++i) ret += ly[i];
	return ret;
}

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		m_size = h_size = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", ma[i]);
			for (int j = 0; j < m; ++j) {
				if (ma[i][j] == 'm') {
					men[m_size++] = make_pair(i, j);
				} else if (ma[i][j] == 'H') {
					house[h_size++] = make_pair(i, j);
				}
			}
		}
		memset(V, 0, sizeof(V));
		nE = 0;
		for (int i = 0; i < m_size; ++i) {
			for (int j = 0; j < h_size; ++j) {
				addEdge(i, j, -(abs(men[i].first - house[j].first) + abs(men[i].second - house[j].second)));
			}
		}
		int ans = -KM(m_size, h_size);
		printf("%d\n", ans);
	}
	return 0;
}
