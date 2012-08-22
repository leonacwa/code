#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 101;
const int MM = 1501;
struct Edge {
	int u, v, w;
};

bool cmpE (const Edge &a, const Edge &b) {
	return a.w < b.w;
}
int n, sum;
int nE;
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
	sort(E, E + nE, cmpE);
	sum = 0;
	for (int i = 0; i < nE; ++i) {
		int fu = find(E[i].u), fv = find(E[i].v);
		if (fu != fv) {
			join(fu, fv);
			sum += E[i].w;
		}
	}
}

int main()
{
	while (EOF != scanf("%d\n", &n) && n > 0) {
		nE = 0;
		for (int i = 1; i < n; ++i) {
			char A, B, s[2];
			int k, w;
			scanf("%s %d", s, &k);
			A = s[0];
			for (int j = 0; j < k; ++j) {
				scanf("%s %d", s, &w);
				B = s[0];
				E[nE].u = A - 'A';
				E[nE].v = B - 'A';
				E[nE].w = w;
				++nE;
			}
		}
		kruskal();
		printf("%d\n", sum);
	}
	return 0;
}
