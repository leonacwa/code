/* hdu_vc_3276 C */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100000 + 100;
int cnt[MAXN];
int l_end[MAXN<<2], r_end[MAXN<<2];

void make_tree(int rt, int L, int R) {
	l_end[rt] = r_end[rt] = -1;
	if (L == R) {
		cnt[L] = 0;
		return;
	}
	int M = (L + R) >> 1;
	make_tree(rt<<1, L, M);
	make_tree(rt<<1|1, M+1, R);
}

void update(int rt, int L, int R, int p, int v) {
	if (L == R && L == p) {
		cnt[p] += v;
		if (cnt[p] <= 0) {
			l_end[rt] = r_end[rt] = -1;
		} else {
			l_end[rt] = r_end[rt] = L;
		}
		return;
	}
	if (L == R) return;
	int M = (L + R) >> 1, LS = rt<<1, RS = rt<<1|1;
	if (p <= M) update(LS, L, M, p, v);
	else update(RS, M+1, R, p, v);

	if (l_end[LS] != -1) l_end[rt] = l_end[LS];
	else l_end[rt] = l_end[RS];
	if (r_end[RS] != -1) r_end[rt] = r_end[RS];
	else r_end[rt] = r_end[LS];

}

int left_most(int rt, int L, int R, int l, int r) {
	if (l <= L && R <= r) {
		return l_end[rt];
	}
	int M = (L + R) >> 1;
	int ret = -1;
	if (l <= M) ret = left_most(rt<<1, L, M, l, r);
	if (ret == -1 && M < r) ret = left_most(rt<<1|1, M+1, R, l, r);
	return ret;
}

int right_most(int rt, int L, int R, int l, int r) {
	if (l <= L && R <= r) {
		return r_end[rt];
	}
	int M = (L + R) >> 1;
	int ret = -1;
	if (M < r) ret = right_most(rt<<1|1, M+1, R, l, r);
	if (ret == -1 && l <= M) ret = right_most(rt<<1, L, M, l, r);
	return ret;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	for (int iCase = 1; iCase <= nTest; ++iCase) {
		int Len, n, p = 0, dir = 1;
		long long ans = 0;
		scanf("%d%d", &Len, &n);
		make_tree(1, 0, Len);
		while (n--) {
			int c, x;
			scanf("%d", &c);
			if (c == 0) {
				scanf("%d", &x);
				update(1, 0, Len, x, 1);
			} else if (c == 1) {
				int l = right_most(1, 0, Len, 0, p);
				int r = left_most(1, 0, Len, p, Len);
				bool eat = true;
				if (l != -1 && r != -1) {
					int a1 = abs(l - p), a2 = abs(r - p);
					if (a1 < a2 || (a1 == a2 && dir == 0)) {
						ans += a1;
						if (l < p) dir = 0;
						p = l;
					} else if (a1 > a2 || (a1 == a2 && dir == 1)) {
						ans += a2;
						if (p < r) dir = 1;
						p = r;
					}
				} else if (l != -1 && r == -1) {
					ans += abs(l - p);
					if (l < p) dir = 0;
					p = l;

				} else if (l == -1 && r != -1) {
					ans += abs(r - p);
					if (p < r) dir = 1;
					p = r;
				} else {
					eat = false;
				}
				if (eat) update(1, 0, Len, p, -1);
			} else {
				for(;;);
			}
		}
		printf("Case %d: %lld\n", iCase, ans);
//		printf("Case %d: %I64d\n", iCase, ans);
	}
	return 0;
}

