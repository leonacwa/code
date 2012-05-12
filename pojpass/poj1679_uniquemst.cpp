#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 101;

struct Edge {
	int u, v, w;
};
bool cmpE(const Edge &a, const Edge &b) {
	return a.w < b.w;
}
int n, m;
int fa[NN];
int cnt;
int opt[NN];
Edge E[NN * NN];
bool dupliate[NN * NN], del[NN * NN];

void init()
{
	for (int i = 0; i <= n; ++i) {
		fa[i] = i;
	}
}

int find(int x) {
	int p;
	for (p = x; p != fa[p]; p = fa[p]) ;
	while (x != fa[x]) {
		int t = fa[x];
		fa[x] = p;
		x = t;
	}
	return p;
}

void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		fa[fy] = fx;
	}
}

int kruskal()
{
	init();
	cnt = 0;
	int sum = 0;
	for (int i = 0; i < m; ++i) {
		if (del[i]) continue;
		int fu = find(E[i].u), fv = find(E[i].v);
		if (fu != fv) {
			join(fu, fv);
			opt[cnt++] = i;
			sum += E[i].w;
		}
		if (cnt == n - 1) break;
	}
	if (cnt != n - 1) return INT_MAX;
	return sum;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].w);
		}
		sort(E, E + m, cmpE);
		int w = -INT_MAX;
		for (int i = 0; i < m; ++i) {
			del[i] = false;
			if (w != E[i].w) {
				dupliate[i] = false;
				w = E[i].w;
			} else {
				dupliate[i] = dupliate[i-1] = true;
			}
		}
		int min1 = kruskal();
		bool uni = true;
		for (int i = 0; i < cnt; ++i) {
			if (dupliate[opt[i]]) {
				del[opt[i]] = true;
				int min2 = kruskal();
				del[opt[i]] = false;
				if (min1 == min2) {
					uni = false;
					break;
				}
			}
		}
		if (uni) {
			printf("%d\n", min1);
		} else {
			puts("Not Unique!");
		}
	}
	return 0;
}

