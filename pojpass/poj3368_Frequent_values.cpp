#include <stdio.h>
#include <string.h>

const int MAXN = 100000+5;
const int INF = 999999999;
struct A {
	int a, id, c;
};
A a[MAXN];

int cnt[MAXN];
int n, q;

struct Seg {
	int l, r;
	int max;
};
Seg ST[MAXN*4];

inline int max(int a, int b) {
	return a > b ? a : b;
}

void build(int k, int l, int r)
{
	ST[k].l = l;
	ST[k].r = r;
	if (l == r) {
		ST[k].max = a[l].c;
	} else {
		int m = (r - l) / 2 + l;
		build(k*2, l, m);
		build(k*2+1, m+1, r);
		ST[k].max = max(ST[k*2].max, ST[k*2+1].max);
	}
}

int query(int k, int l, int r)
{
	if (r < ST[k].l || ST[k].r < l) {
		return 0;
	}
	if (l <= ST[k].l && ST[k].r <= r) {
		return ST[k].max;
	} else {
		return max(query(k*2, l, r), query(k*2+1, l, r));
	}
}

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		scanf("%d", &q);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i].a);
		}
		memset(cnt, 0, sizeof(cnt));
		int id = 1;
		int c = 1;
		a[0].c = 0;
		a[0].id = 0;
		cnt[0] = 0;
		a[1].id = id;
		a[1].c = c;
		cnt[1] = 1;
		for (int i = 2; i <= n; i++) {
			if (a[i-1].a != a[i].a) {
				id++;
				c = 1;
			} else {
				c++;
			}
			a[i].c = c;
			a[i].id = id;
			cnt[id]++;
		}
		build(1, 1, n);
		while (q--) {
			int i, j, ans = 0;
			scanf("%d %d", &i, &j);
			if (a[i].id == a[j].id) {
				ans = j - i + 1;
			} else if (a[i].id + 1 == a[j].id) {
				ans = max(j-i+1-a[j].c, a[j].c);
			} else {
				int l = cnt[a[i].id];
				if (a[i].id == a[i-1].id) {
					l -= a[i-1].c;
				}
				ans = max(l, query(1, i+l, j));
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}

