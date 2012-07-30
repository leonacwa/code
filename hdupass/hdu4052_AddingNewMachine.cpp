#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long int64;

const int MAXN = 100005;

struct Rect {
	int x1, x2, y1, y2;
} rect[MAXN];
struct Seg {
	int l, r, h, v;
	Seg(int tl = 0, int tr = 0, int th = 0, int tv = 0) : l(tl), r(tr), h(th), v(tv) {}
	bool operator < (const Seg &B) const {
		if (h != B.h) return h < B.h;
		return v < B.v;
	}
} ss[MAXN];

int xa[MAXN * 4], xc;
int cnt[MAXN * 12], llen[MAXN * 12], rlen[MAXN * 12];
int64 sum[MAXN * 12];

int BinX(int x) {
	int l = 0, r = xc-1, m;
	while (l <= r) {
		m = (l + r) >> 1;
		if (xa[m] == x) return m;
		if (xa[m] < x) l = m + 1;
		else r = m - 1;
	}
	return -1;
}
inline int getSum(int l, int m) {
	return l >= m ? l - m + 1: 0;
}

inline int getLen(int L, int R) {
   return  xa[R+1] - xa[L];
}

void UpdateData(int rt, int L, int R, int m)
{
	if (cnt[rt] == 0) {
		if (L < R) {
			int LS = rt<<1, RS = rt<<1|1, M = (L+R)>>1;
			sum[rt] = sum[LS] + sum[RS];
			int l = min(m-1, rlen[LS]) + min(m-1, llen[RS]);
			sum[rt] += getSum(l, m);
		} else {
			int l = getLen(L, R);
			sum[rt] = getSum(l, m);
		}
	} else {
		sum[rt] = 0;
	}
}

void PushUp(int rt, int L, int R, int m) {
	if (cnt[rt]) {
		llen[rt] = rlen[rt] = 0;
	} else if (L < R) {
		int LS = rt<<1, RS = rt<<1|1, M = (L+R)>>1, l;
		l = getLen(L, M);
		llen[rt] = llen[LS] + (llen[LS] == l ? llen[RS] : 0);
		l = getLen(M+1, R);
		rlen[rt] = rlen[RS] + (rlen[RS] == l ? rlen[LS] : 0);
	} else {
		llen[rt] = rlen[rt] = getLen(L, R);
	}
	UpdateData(rt, L, R, m);
}

void make_tree(int rt, int L, int R, int m)
{
	cnt[rt] = 0;
	llen[rt] = rlen[rt] = getLen(L, R);
	if (L == R) {
		int l = getLen(L, R);
		sum[rt] = getSum(l, m);
		return;
	}
	make_tree(rt<<1, L, (L+R)>>1, m);
	make_tree(rt<<1|1, ((L+R)>>1) + 1, R, m);
	UpdateData(rt, L, R, m);
}

void update(int rt, int L, int R, int l, int r, int v, int m) 
{
	if (l <= L && R <= r) {
		cnt[rt] += v;
		llen[rt] = rlen[rt] = (cnt[rt] ? 0 : getLen(L, R));
		UpdateData(rt, L, R, m);
		return;
	}
	if (L >= R) return;
	int M = (L+R)>>1;
	if (l <= M) update(rt<<1, L, M, l, r, v, m);
	if (M < r) update(rt<<1|1, M+1, R, l, r, v, m);
	PushUp(rt, L, R, m);
}

int64 solve(int w, int h, int n, int m, Rect rect[])
{
	xc = 0;
	xa[xc++] = 1;
	xa[xc++] = w;
	xa[xc++] = w+1;
	int ss_cnt = 0;
	ss[ss_cnt++] = Seg(1, w, 0, 0);
	ss[ss_cnt++] = Seg(1, w, h, 0);
	for (int i = 0; i < n; ++i) {
		int x1 = rect[i].x1, x2 = rect[i].x2;
		xa[xc++] = x1;
		xa[xc++] = x2;
		if (x1 > 1) xa[xc++] = x1 - 1;
		if (x1 < w) xa[xc++] = x1 + 1;
		if (x2 > 1) xa[xc++] = x2 - 1;
		if (x2 < w) xa[xc++] = x2 + 1;
		ss[ss_cnt++] = Seg(x1, x2, rect[i].y1-1, 1);
		ss[ss_cnt++] = Seg(x1, x2, rect[i].y2, -1);
	}
	sort(ss, ss+ss_cnt);
	ss[ss_cnt] = ss[ss_cnt-1];
	sort(xa, xa+xc);
	int t = 1;
	for (int i = 1; i < xc; ++i) {
		if (xa[i] != xa[i-1]) xa[t++] = xa[i];
	}
	xc = t;
	make_tree(1, 0, xc-2, m);
	int64 ret = 0;
	for (int i = 0; i < ss_cnt; ++i) {
		int l = BinX(ss[i].l), r = BinX(ss[i].r);
		if (ss[i].l <= ss[i].r) update(1, 0, xc-2, l, r, ss[i].v, m);
		int64 height = ss[i+1].h - ss[i].h;
		if (height > 0 && sum[1] > 0) ret += height * sum[1];
	}
	return ret;
}

int main()
{
	int w, h, n, m;
	while (EOF != scanf("%d%d%d%d", &w, &h, &n, &m)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);
		}
		int64 ans = solve(w, h, n, m, rect);
		if (m > 1) {
			for (int i = 0; i < n; ++i) {
				swap(rect[i].x1, rect[i].y1);
				swap(rect[i].x2, rect[i].y2);
			}
			ans += solve(h, w, n, m, rect);
		}
		//printf("%lld\n", ans);
		printf("%I64d\n", ans);
		// 大整数的输出永远的痛
	}
	return 0;
}

