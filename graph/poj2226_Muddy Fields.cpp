/*
 * POJ 2226 Muddy Fields
 * 二分图最小点覆盖
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 25 * 50, MAXM = MAXN * 50;

struct Edge {
	int to;
	Edge *next;
};
int nE;
Edge E[MAXM], *V[MAXN];
int mat[51][51];

int match[MAXN];
int nmk;
int mk[MAXN];

void addEdge(int u, int v) {
	Edge *e = E + nE++;
	e->to = v;
	e->next = V[u];
	V[u] = e;
}

bool dfs(int u) {
	for (Edge *e = V[u]; e; e = e->next) {
		if (mk[e->to] == nmk) continue;
		mk[e->to] = nmk;
		if (match[e->to] == -1 || dfs(match[e->to])) {
			match[e->to] = u;
			return true;
		}
	}
	return false;
}

int max_match(int n) {
	memset(match, -1, sizeof(match));
	int cnt = 0;
	nmk = 0;
	memset(mk, 0, sizeof(mk));
	for (int i = 0; i < n; ++i) {
		++nmk;
		if (dfs(i)) ++cnt;
	}
	return cnt;
}

int main() {
	int r, c;
	while (EOF != scanf("%d%d", &r, &c)) {
		memset(V, 0, sizeof(V));
		nE = 0;
		int ns = 0;
		for (int i = 0; i < r; ++i) {
			char str[64];
			scanf("%s", str);
			bool can = false;
			for (int j = 0; j < c; ++j) {
				if (str[j] == '*') {
					mat[i][j] = ns;
					can = true;
				} else {
					mat[i][j] = -1;
					if (can) {
						++ns;
						can = false;
					}
				}
			}
			if (can) ++ns;
		}
		int ns2 = 0;
		for (int i = 0; i < c; ++i) {
			bool can = false;
			for (int j = 0; j < r; ++j) {
				if (mat[j][i] != -1) {
					addEdge(mat[j][i], ns2);
					can = true;
				} else if (mat[j][i] == -1) {
					if (can) {
						++ns2;
						can =  false;
					}
				}
			}
			if (can) ++ns2;
		}
		//printf("r c %d %d\n", ns, ns2);
		printf("%d\n", max_match(ns));
	}
	return 0;
}
