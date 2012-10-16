/*
 * ZOJ 3659 Conquer a New Region
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 200005;

struct Edge {
	int a, b, c;
	bool operator < (const Edge &o) const {
		return c > o.c;
	}
};
Edge E[MAXN];

struct Tree {
	Tree *l, *r;
	int sz;
	LL cost;
};
Tree T[MAXN*2], *pT[MAXN*2];

int fa[MAXN];
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n-1; ++i) {
			scanf("%d%d%d", &E[i].a, &E[i].b, &E[i].c);
			--E[i].a;
			--E[i].b;
		}
		sort(E, E+n-1);
		for (int i = 0; i < n; ++i) {
			T[i].sz = 1;
			T[i].l = T[i].r = NULL;
			T[i].cost = 0;
			pT[i] = T + i;
			fa[i] = i;
		}
		int nTs = n;
		for (int i = 0; i < n-1; ++i) {
			int a = find(E[i].a), b = find(E[i].b), c = E[i].c;
			Tree *mt = T + nTs++;
			mt->cost = 0;
			mt->sz = pT[a]->sz + pT[b]->sz;
			mt->l = pT[a];
			mt->r = pT[b];
			pT[a]->cost += (LL)pT[b]->sz * c;
			pT[b]->cost += (LL)pT[a]->sz * c;
			fa[a] = b;
			pT[b] = mt;
		}
		for (int i = nTs-1; i >= 0; --i) {
			Tree *t = T + i;
			if (t->l != NULL) {
				t->l->cost += t->cost;
				t->r->cost += t->cost;
			}
		}
		LL ans = -1;
		for (int i = 0; i < n; ++i) {
			if (ans < T[i].cost) ans = T[i].cost;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
