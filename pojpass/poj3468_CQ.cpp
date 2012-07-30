#include <cstdio>
typedef long long llong;
const int MAXN = 100000 + 10;
llong add[MAXN << 2];
llong sum[MAXN << 2];
int a[MAXN];

void PushUp(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void PushDown(int rt, int l) {
	if (add[rt]) {
		int ls = rt << 1, rs = rt << 1 | 1;
		add[ls] += add[rt];
		add[rs] += add[rt];
		sum[ls] += add[rt] * (l - (l >> 1));
		sum[rs] += add[rt] * (l >> 1);
		add[rt] = 0;
	}
}

void build(int rt, int l, int r)
{
	add[rt] = 0;
	if (l == r) {
		sum[rt] = a[l];
		return;
	}
	int m = (l + r) >> 1;
	build(rt << 1, l, m);
	build(rt << 1 | 1, m + 1, r);
	PushUp(rt);
}

void update(int rt, int l, int r, int L, int R, int c)
{
	if (L <= l && r <= R) {
		add[rt] += c;
		sum[rt] += (llong)c * (r - l + 1);
		return;
	}
	PushDown(rt, r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) update(rt << 1, l, m, L, R, c);
	if (m < R) update(rt << 1 | 1, m + 1, r, L, R, c);
	PushUp(rt);
}

llong query(int rt, int l, int r, int L, int R)
{
	if (L <= l && r <= R) {
		return sum[rt];
	}
	PushDown(rt, r - l + 1);
	llong ret = 0;
	int m = (l + r) >> 1;
	if (L <= m) ret += query(rt << 1, l, m, L, R);
	if (m < R) ret += query(rt << 1 | 1, m + 1, r, L, R);
	return ret;
}

int main()
{
	int n, q;
	while (EOF != scanf("%d%d", &n, &q)) {
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		build(1, 1, n);
		while (q--) {
			char cmd[32];
			int a, b, c;
			scanf("%s%d%d", cmd, &a, &b);
			if (cmd[0] == 'Q') {
				printf("%lld\n", query(1, 1, n, a, b));
				//printf("%I64d\n", query(1, 1, n, a, b));
			} else if (cmd[0] == 'C')  {
				scanf("%d", &c);
				update(1, 1, n, a, b, c);
			} else {
				while(1);
			}
		}
	}
	return 0;
}

