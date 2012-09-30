/* HDU 4419 Colourful Rectangle
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long int64;

const int fx[7] = {1, 2, 4, 3, 5, 6, 7};
const int MAXN = 10005;

int64 ans[8];

struct Seg {
	int l, r, h;
	int v;
	int c;
	Seg() {}
	Seg(int tl, int tr, int th, int tv, int tc) {
		l = tl, r = tr, h = th, v = tv, c = tc;
	}
	bool operator < (const Seg &B) const {
		if (h != B.h) return h < B.h;
		return v < B.v;
	}
};
Seg ss[MAXN<<2];
int Xo_cnt;
int Xo[MAXN<<2];

struct Node {
	int c[3];
	int64 s[8];
};
Node T[MAXN<<2];

#define lson (rt<<1)
#define rson (rt<<1|1)

void make_tree(int rt, int L, int R) {
	memset(&T[rt], 0, sizeof(Node));
	T[rt].s[0] = Xo[R] - Xo[L-1];
	if (L == R) return;
	int M = (L+R)>>1;
	make_tree(lson, L, M);
	make_tree(rson, M+1, R);
}

void push_up(int rt, int L, int R) {
	int c = 0;
	for (int i = 0; i < 3; ++i) if (T[rt].c[i] > 0) c |= (1<<i);
	for (int i = 0; i < 8; ++i) T[rt].s[i] = 0;
	if (L == R) {
		T[rt].s[c] = Xo[R] - Xo[L-1];
	} else {
		for (int i = 0; i < 8; ++i) T[rt].s[i|c] += T[lson].s[i] + T[rson].s[i];
	}
}

bool update(int rt, int L, int R, int l, int r, int c, int v) {
	if (l <= L && R <= r) {
		T[rt].c[c] += v;
		push_up(rt, L, R);
		return true;
		if ((v == -1 && T[rt].c[c] == 0) || (v == 1 && T[rt].c[c] == 1)) {
			push_up(rt, L, R);
			return true;
		}
		return false;
	}
	int M = (L + R) >> 1;
	bool ch = false;
	if (l <= M) ch = update(lson, L, M, l, r, c, v);
	if (M < r) if ( update(rson, M+1, R, l, r, c, v) ) ch = true;
	if (ch) push_up(rt, L, R);
	return ch;
}

int main() {
	int runs;
	scanf("%d", &runs);
	for (int ca = 1; ca <= runs; ++ca) {
		int n, s_cnt = 0;
		Xo_cnt = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			char c[2];
			int x1, x2, y1, y2, co;
			scanf("%s%d%d%d%d", c, &x1, &y1, &x2, &y2);
			if (c[0] == 'R') co = 0;
			else if (c[0] == 'G') co = 1;
			else if (c[0] == 'B') co = 2;
			ss[s_cnt++] = Seg(x1, x2, y1, 1, co);
			ss[s_cnt++] = Seg(x1, x2, y2, -1, co);
			Xo[Xo_cnt++] = x1;
			Xo[Xo_cnt++] = x2;
		}
		sort(Xo, Xo + Xo_cnt);
		Xo_cnt = unique(Xo, Xo+Xo_cnt) - Xo;
		/*
		for (int i = 0; i < Xo_cnt; ++i) printf("%d ", Xo[i]); puts(" ");
		for (int i = 0; i < Xo_cnt; ++i)
		printf("find %d:%d\n", Xo[i], lower_bound(Xo, Xo+Xo_cnt, Xo[i]) - Xo);
		*/
		sort(ss, ss+s_cnt);
		int L = 1, R = Xo_cnt - 1;
		make_tree(1, L, R);
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < s_cnt-1; ++i) {
			int l = lower_bound(Xo, Xo+Xo_cnt, ss[i].l) + 1 - Xo;
			int r = lower_bound(Xo, Xo+Xo_cnt, ss[i].r) - Xo;
			update(1, L, R, l, r, ss[i].c, ss[i].v);
			if (ss[i].h < ss[i+1].h) {
				int64 h = ss[i+1].h - ss[i].h;
				Node &t = T[1];
				for (int i = 1; i < 8; ++i) ans[i] += t.s[i] * h;
	//			for (int i = 0; i < 7; ++i) printf("%lld  ", ans[fx[i]]); puts(" ");
			}
		}
		printf("Case %d:\n", ca);
		for (int i = 0; i < 7; ++i) printf("%lld\n", ans[fx[i]]);
	}
	return 0;
}
