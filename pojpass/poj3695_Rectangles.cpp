/* 线段树
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1005, MAX_RECT = 25;
struct Rect {
	int x1, x2, y1, y2;
} rect[MAX_RECT];

struct Seg {
	int l, r, h, v;
	Seg(int tl=0, int tr=0, int th=0, int tv=0) : l(tl), r(tr), h(th), v(tv) {}
	bool operator < (const Seg &B) const {
		if (h != B.h) return h < B.h;
		return v < B.v;
	}
} ss[MAX_RECT * 2];

int xc, xa[MAX_RECT * 2];

int cnt[MAXN<<2];
int sum[MAXN<<2];

int Bin(int x) {
	int l = 0, r = xc - 1, m;
	while (l <= r) {
		m = (l + r) >> 1;
		if (xa[m] == x) return m;
		if (xa[m] < x) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

void init()
{
	memset(cnt, 0, sizeof(cnt));
	memset(sum, 0, sizeof(sum));
}

void PushUp(int rt, int L, int R)
{
	if (cnt[rt] > 0) {
		sum[rt] = xa[R+1] - xa[L];
	} else if (L == R) {
		sum[rt] = 0;
	} else {
		sum[rt] = sum[rt<<1] + sum[rt<<1|1];
	}
}

void update(int rt, int L, int R, int l, int r, int v)
{
	if (l <= L && R <= r) {
		cnt[rt] += v;
		PushUp(rt, L, R);
		return;
	}
	int M = (L + R) >> 1;
	if (l <= M) update(rt<<1, L, M, l, r, v);
	if (M < r) update(rt<<1|1, M+1, R, l, r, v);
	PushUp(rt, L, R);
}

int main()
{
	int nCase = 0, n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		xc = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);
			xa[xc++] = rect[i].x1;
			xa[xc++] = rect[i].x2;
		}
		sort(xa, xa + xc);
		int t = 1;
		for (int i = 1; i < xc; ++i) {
			if (xa[i] != xa[i-1]) xa[t++] = xa[i];
		}
		xc = t;
		printf("Case %d:\n", ++nCase);
		for (int q = 1; q <= m; ++q) {
			int r, i, ss_cnt = 0;
			scanf("%d", &r);
			while (r--) {
				scanf("%d", &i);
				ss[ss_cnt++] = Seg(rect[i].x1, rect[i].x2, rect[i].y1, 1);
				ss[ss_cnt++] = Seg(rect[i].x1, rect[i].x2, rect[i].y2, -1);
			}
			sort(ss, ss+ss_cnt);
			ss[ss_cnt] = ss[ss_cnt-1];
			int ans = 0;
			for (int j = 0; j < ss_cnt; ++j) {
				update(1, 0, xc-1, Bin(ss[j].l), Bin(ss[j].r)-1, ss[j].v);
				ans += sum[1] * (ss[j+1].h -ss[j].h);
			}
			printf("Query %d: %d\n", q, ans);
		}
		puts("");
	}
	return 0;
}

