/* HDU 4263 Red/Blue Spanning Tree
 * 最小生成树的变形
 * 教训：没好好读题就是错
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 1005;
const int MAXM = MAXN * MAXN;

struct Edge {
	int u, v;
	Edge() {}
	Edge(int tu, int tv) : u(tu), v(tv) {}
} RE[MAXM], BE[MAXM];
int nRE, nBE;

int fa[MAXN];
void init_fa(int n) {
	for (int i = 0; i <= n; ++i) fa[i] = i;
}
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) fa[fy] = fx;
}

int main() {
	int n, m, k;
	while (EOF != scanf("%d%d%d", &n, &m, &k)) {
		if (n == 0 && m == 0 && k == 0) break;
		nRE = nBE = 0;
		for (int i = 0; i < m; ++i) {
			char c[2];
			int f, t;
			scanf("%s %d%d", c, &f, &t);
			if (c[0] == 'R') {
				RE[nRE++] = Edge(f, t);
			} else if (c[0] == 'B') {
				BE[nBE++] = Edge(f, t);
			}
		}
		if (nBE < k) {
			puts("0");
			continue;
		}
		init_fa(n);
		Edge e;
		int cnt = 0, b_cnt = 0;
		for (int i = 0; cnt < n-1 && i < m; ++i) {
			if (i < nRE) e = RE[i];
			else e = BE[i - nRE];
			if (find(e.u) != find(e.v)) {
				join(e.u, e.v);
				++cnt;
				if (i >= nRE) ++b_cnt;
			}
		}
		if (b_cnt < k) {
			init_fa(n);
			cnt = b_cnt = 0;
			for (int i = 0; i < m && cnt < n-1 && b_cnt < k; ++i) {
				if (i < nBE) e = BE[i];
				else e = RE[i - nBE];
				if (find(e.u) != find(e.v)) {
					join(e.u, e.v);
					++cnt;
					if (i < nBE) ++b_cnt;
				}
			}
		} else if (b_cnt > k) { // 尼玛，k还有0的时候，我写了b_cnt = 0 WA得不明不白
			b_cnt = -1;
		}
		puts(b_cnt >= k ? "1" : "0");
	}
	return 0;
}
