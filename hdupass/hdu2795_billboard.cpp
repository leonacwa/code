#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 200000 + 10;

int h, w, n;
int Max[MAXN * 4];

void build(int rt, int l, int r)
{
	Max[rt] = w;
	if (l == r) return;
	int m = (l + r) >> 1;
	build(rt << 1, l, m);
	build(rt << 1 | 1, m + 1, r);
}

int query(int rt, int l, int r, int x)
{
	if (l == r) {
		Max[rt] -= x;
		return l;
	}
	int m = (l + r) >> 1;
	int ret = (Max[rt << 1] >= x) ? query(rt << 1, l, m, x) : query(rt << 1 | 1, m+1, r, x);
	Max[rt] = max(Max[rt << 1], Max[rt << 1 | 1]);
	return ret;
}

int main()
{
	while (EOF != scanf("%d%d%d", &h, &w, &n)) {
		if (h > n) h = n;
		build(1, 1, h);
		while (n--) {
			int x;
			scanf("%d", &x);
			if (Max[1] < x) puts("-1");
			else printf("%d\n", query(1, 1, h, x));
		}
	}
	return 0;
}

