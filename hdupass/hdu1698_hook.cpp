/* 线段树 
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 100000 + 10;

int sum[MAXN << 2];
int col[MAXN << 2];

void PushUp(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void PushDown(int rt, int l) {
	if (col[rt]) {
		int ls = rt << 1, rs = rt << 1 | 1;
		col[ls] = col[rs] =  col[rt];
		sum[ls] = (l - (l >> 1)) * col[ls];
		sum[rs] = (l >> 1) * col[rs];
		col[rt] = 0;
	}
}

void build(int rt, int l, int r)
{
	col[rt] = 1;
	sum[rt] = 1;
	if (l == r) return;
	int m = (l + r) >> 1;
	build(rt << 1, l, m);
	build(rt << 1 | 1, m + 1, r);
	PushUp(rt);
}

void update(int rt, int l, int r, int L, int R, int c)
{
	if (L <= l && r <= R) {
		col[rt] = c;
		sum[rt] = (r - l + 1) * c;
		return;
	}
	PushDown(rt, r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) update(rt << 1, l, m, L, R, c);
	if (m < R) update(rt << 1 | 1, m + 1, r, L, R, c);
	PushUp(rt);
}

int main()
{
	int nTest, nCase = 0;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, q;
		scanf("%d%d", &n, &q);
		build(1, 1, n);
		while (q--) {
			int l, r, c;
			scanf("%d%d%d", &l, &r, &c);
			update(1, 1, n, l, r, c);
		}
		printf("Case %d: The total value of the hook is %d.\n", ++nCase, sum[1]);
	}
	return 0;
}

