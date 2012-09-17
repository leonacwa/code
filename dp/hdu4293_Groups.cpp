/* HDU 4293 Groups
 * 转换成区间DP做
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node {
	int l, r;
	int c;
	bool operator < (const Node &b) const {
		if (l != b.l) return l < b.l;
		return r < b.r;
	}
};
Node p[501];

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (a+b >= n) continue;
			p[cnt].c = 1;
			p[cnt].l = a;
			p[cnt].r = n - b;
			++cnt;
		}
		sort(p, p + cnt);
		int t = 0;
		for (int i = 1; i < cnt; ++i) {
			if (p[t].l == p[i].l && p[t].r == p[i].r) {
				if (p[t].c < p[t].r - p[t].l) ++p[t].c;
			} else {
				p[++t] = p[i];
			}
		}
		cnt = t + 1;
		int ans = p[0].c;
		for (int i = 1; i < cnt; ++i) {
			int t = 0;
			for (int j = 0; j < i; ++j) {
				if (p[j].r <= p[i].l && t < p[j].c) {
					t = p[j].c;
				}
			}
			p[i].c += t;
			if (ans < p[i].c) ans = p[i].c;
		}
		printf("%d\n", ans);
	}
	return 0;
}
