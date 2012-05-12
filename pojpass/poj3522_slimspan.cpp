/* kruskal + 枚举
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 101;
const int MM = NN * (NN-1) / 2;
struct Edge {
	int u, v, w;
};
bool cmpEdge(const Edge &a, const Edge &b) {
	return a.w < b.w;
}
int nE, n, m;
Edge E[MM];
int set[NN];

void init() {
	for (int i = 0; i <= n; ++i) {
		set[i] = i;
	}
}
int find(int x) {
	if (x != set[x]) {
		set[x] = find(set[x]);
	}
	return set[x];
}

void join(int a, int b) {
	int fa = find(a), fb = find(b);
	if (fa != fb) {
		set[fb] = fa;
	}
}

int kruskal(int l, int r)
{
	init();
	int minE = INT_MAX, maxE = -INT_MAX;
	for (int i = l; i <= r; ++i) {
		int fu = find(E[i].u), fv = find(E[i].v);
		if (fu != fv) {
			join(fu, fv);
			if (minE >= INT_MAX) {
				minE = E[i].w;
			}
			maxE = max(maxE, E[i].w);
		}
	}
	int f1 = find(1);
	for (int i = 2; i <= n; ++i) {
		if (f1 != find(i)) {
			return INT_MAX;
		}
	}
	return maxE - minE;
}

int main()
{
	while (EOF != scanf("%d %d", &n, &m) && !(n == 0 && m == 0)) {
		for (int i = 0; i < m; ++i) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			E[i].u = u;
			E[i].v = v;
			E[i].w = w;
		}
		nE = m;
		sort(E, E + nE, cmpEdge);
		int ans = kruskal(0, nE-1);
		if (ans != INT_MAX) {
			for (int l = 0; l < nE; ++l) {
				int t = kruskal(l, nE-1);
				if (t == INT_MAX) break;
				if (ans > t) {
					ans = t;
				}
			}
		}
		if (ans == INT_MAX) {
			printf("-1\n");
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
}

