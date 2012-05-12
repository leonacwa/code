#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 1001;
const int MM = 15001;
struct Edge {
	int u, v, w;
};
bool cmpE (const Edge &a, const Edge &b) {
	return a.w < b.w;
}
int n, m, sum;
Edge E[MM];
int fa[NN];

void init()
{
	for (int i = 0; i <= n; ++i) {
		fa[i] = i;
	}
}

int find(int x)
{
	int p;
	for (p = x; p != fa[p]; p = fa[p]) ;
	while (x != fa[x]) {
		int t = fa[x];
		fa[x] = p;
		x = t;
	}
	return p;
}

void join(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		fa[fy] = fx;
	}
}

void kruskal()
{
	init();
	sort(E, E + m, cmpE);
	sum = 0;
	for (int i = 0; i < m; ++i) {
		int fu = find(E[i].u), fv = find(E[i].v);
		if (fu != fv) {
			join(fu, fv);
			sum += E[i].w;
		}
	}
}

int main()
{
	while (EOF != scanf("%d %d", &n, &m) && n > 0) {
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].w);
		}
		kruskal();
		printf("%d\n", sum);
	}
	return 0;
}

