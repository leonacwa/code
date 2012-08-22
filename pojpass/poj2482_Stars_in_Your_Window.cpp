#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10000+5;

struct Node {
	int v, max, l, r;
};
Node ST[MAXN*16];

struct Point {
	int c;
	double x, y;
};
Point pt[MAXN];
double W, H, w2, h2;
int n;

struct Item {
	double v;
	int id, nv;
	static bool cmp_v(const Item& a, const Item& b) {
		return a.v < b.v;
	}
	static bool cmp_id(const Item& a, const Item& b) {
		return a.id < b.id;
	}
	static bool cmp_nv(const Item& a, const Item& b) {
		return a.nv < b.nv;
	}
};
Item Y[MAXN*2];

struct Seg {
	int b, e;
	double v;
	bool in;
	int c;
	static bool cmp_v(const Seg&a, const Seg&b) {
		return a.v < b.v;
	}
};
Seg XS[MAXN*2];

void build(int k, int l, int r)
{
	ST[k].l = l;
	ST[k].r = r;
	ST[k].v == 0;
	ST[k].max = 0;
	if (l + 1 == r) {
		return;
	}
	int m = (r - l) / 2 + l;
	build(k*2, l, m);
	build(k*2+1, m, r);
}

void add(int k, int l, int r, int v)
{
	if (r <= ST[k].l || ST[k].r <= l) {
		return;
	}
	int c1 = k*2, c2 = k*2+1;
	if (l <= ST[k].l && ST[k].r <= r) {
		ST[k].v += v;
	} else {
		int m = (r - l) / 2 + l;
		add(c1, l, r, v); // !!!!!!!!!!!!!!!
		add(c2, l, r, v); // !!!!!!!!!!!!!!!
	}
	ST[k].max = max(ST[c1].max, ST[c2].max) + ST[k].v;
}

int main()
{
	while (EOF != scanf("%d %lf %lf", &n, &W, &H)) {
		W -= 0.01;
		H -= 0.01;
		w2 = W / 2;
		h2 = H / 2;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %d", &pt[i].x, &pt[i].y, &pt[i].c);
			Y[i*2].id = i*2;
			Y[i*2].v = pt[i].y - h2;
			Y[i*2+1].id = i*2 + 1;
			Y[i*2+1].v = pt[i].y + h2;
		}

		sort(Y, Y+2*n, Item::cmp_v);
		int nv = 0;
		Y[0].nv = 0;
		for (int i = 1; i < 2*n; i++) {
			if (Y[i-1].v != Y[i].v) {
				nv++;
			}
			Y[i].nv = nv;
		}
		sort(Y, Y+2*n, Item::cmp_id);
		for (int i = 0; i < n; i++) {
			XS[i*2].v = pt[i].x - w2;
			XS[i*2].b = Y[i*2].nv;
			XS[i*2].e = Y[i*2+1].nv;
			XS[i*2].in = true;
			XS[i*2].c = pt[i].c;

			XS[i*2+1].v = pt[i].x + w2;
			XS[i*2+1].b = Y[i*2].nv;
			XS[i*2+1].e = Y[i*2+1].nv;
			XS[i*2+1].in = false;
			XS[i*2+1].c = pt[i].c;
		}
		sort(XS, XS+2*n, Seg::cmp_v);

		build(1, 0, nv);
		int max_c = 0;
		for (int i = 0; i < 2*n; i++) {
			if (XS[i].in) {
				add(1, XS[i].b, XS[i].e, XS[i].c);
				max_c = max(ST[1].max, max_c);
			} else {
				add(1, XS[i].b, XS[i].e, -XS[i].c);
			}
		}
		printf("%d\n", max_c);
	}
	return 0;
}

